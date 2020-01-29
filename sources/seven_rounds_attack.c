#include	"../klein.h"
static Bool	find_good_couples(u_klein goodCouples[GOOD_COUPLES_NB][4], u_klein const d);
static Bool	extract_couples_from_file(u_klein goodCouples[GOOD_COUPLES_NB][4], u_klein const d);


Bool	seven_rounds_attack(u_klein masterKey)
{
	u_klein		goodCouples[GOOD_COUPLES_NB][4];
	u_klein		d;
	u_klein		kTilde;
	int			cntError, i;

	printf("start seven round attack\n");

	init_d(d);


	if(!find_good_couples(goodCouples, d))
		return 0;

	printf("start kTilde search\n");
	str2u_klein(kTilde, "0x0000000000000000");
	for(long long k = 0 ; k < MAX_LONG ; k++)
	{
		halfkey(kTilde, k);

		if ((k!=0) && !(k%100000000))
		{
			printf("\ttest number : %lld\t current u_klein : ", k);
			display_u_klein(kTilde);
			printf("\n");
		}

		cntError = 0; i = -1;
		while(cntError <= ERROR_THRESHOLD && ++i < GOOD_COUPLES_NB)
			if(!verify_kTilde(kTilde, goodCouples[i]))
				cntError++;
		if(cntError <= ERROR_THRESHOLD)
		{
			print_u_klein(kTilde,"Good k tilde found");
			printf("\n");
			if(find_full_key(masterKey, kTilde, goodCouples))
				return 1;
			printf("Unsuccessful\n");
		}
	}
	return 0;
}


static Bool	find_good_couples(u_klein goodCouples[GOOD_COUPLES_NB][4], u_klein const d)
{
	u_klein		m1, m2;
	int			cnt;
	long long 	nbTest=0;

	if(extract_couples_from_file(goodCouples, d))		
		return 1;

	printf("searching for couples\n");

	cnt = 0;
	while(cnt < GOOD_COUPLES_NB)
	{
		random_u_klein_haynes(m1);
		u_klein_xor(m2, m1, d);

		nbTest++;
		if (!(nbTest%100000000))
		{
			printf("\ttest number : %lld\t current u_klein : ", nbTest);
			display_u_klein(m1);
			printf("\n");
		}


		if(verify_good_couple_condition(m1, m2) && add_good_couple(goodCouples, m1, m2, cnt))
		{
			cnt++;
			print_u_klein(m1, "\tGood couple found");
		}
	}
	return 1;
}


static Bool	extract_couples_from_file(u_klein goodCouples[GOOD_COUPLES_NB][4], u_klein const d)
{
	FILE	*fd;
	char	filename[UKLEIN_STRING_LENGTH + 27];
	char	buf[UKLEIN_STRING_LENGTH + 2];

	sprintf(filename, "couples/seven_rounds/%s.txt", MASTER_KEY);
	fd = fopen(filename, "r");
	if(!fd)
		return 0;
	for(int i = 0 ; i < GOOD_COUPLES_NB ; i++)
	{
		fgets(buf, UKLEIN_STRING_LENGTH + 2, fd);
		buf[UKLEIN_STRING_LENGTH] = '\0';	// remove '\n'
		str2u_klein(goodCouples[i][0], buf);
		u_klein_xor(goodCouples[i][1], goodCouples[i][0], d);
		oracle(goodCouples[i][2], goodCouples[i][0]);
		oracle(goodCouples[i][3], goodCouples[i][1]);
	}
	fclose(fd);
	printf("goodCouples extract from %s\n", filename);
	return 1;
}


Bool	verify_good_couple_condition(u_klein m1, u_klein m2)
{
	u_klein	c1, c2;
	u_klein	cipherDifferential;

	oracle(c1, m1);
	oracle(c2, m2);
	u_klein_xor(cipherDifferential, c1, c2);
	unmix_nibbles(cipherDifferential, cipherDifferential);

	for(int i = 0 ; i < NIBBLES_NB_DIV2 ; i++)
		if(cipherDifferential[2 * i])
			return 0;
	return 1;
}


Bool	add_good_couple(u_klein goodCouples[GOOD_COUPLES_NB][4], u_klein m1, u_klein m2, int cnt)
{
	for(int i = 0 ; i < GOOD_COUPLES_NB ; i++)
			if(!u_klein_cmp(m1, goodCouples[i][0]) || !u_klein_cmp(m1, goodCouples[i][1]))
				return 0;

	u_klein_dcp(goodCouples[cnt][0], m1);
	u_klein_dcp(goodCouples[cnt][1], m2);
	oracle(goodCouples[cnt][2], m1);
	oracle(goodCouples[cnt][3], m2);
	return 1;
}


void	init_d(u_klein d)
{
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		d[i] = 0;
	d[5] = 0xb;
	print_u_klein(d,"differential initialization");
}


void	halfkey(u_klein kTilde, long long k)
{
	for(int i = NIBBLES_NB_DIV2 - 1 ; i >= 0 ; i--)
	{
		kTilde[2 * i + 1] = k % 16;
		k /= 16;
	}
}


Bool 	verify_kTilde(u_klein const kTilde, u_klein const goodCouples[4])
{
	u_klein 	cipherDifferential;
	u_klein		c1, c2;

	u_klein_dcp(c1, goodCouples[2]);
	u_klein_dcp(c2, goodCouples[3]);

	unmix_nibbles(c1, c1);
	unmix_nibbles(c2, c2);
	unrotate_nibbles(c1, c1);
	unrotate_nibbles(c2, c2);
	add_round_key(c1, c1, kTilde);
	add_round_key(c2, c2, kTilde);
	sub_nibbles(c1, c1);
	sub_nibbles(c2, c2);
	unmix_nibbles(c1, c1);
	unmix_nibbles(c2, c2);

	u_klein_xor(cipherDifferential, c1, c2);

	for(int i = 0 ; i < NIBBLES_NB_DIV2 ; i++)
		if(cipherDifferential[2 * i])
			return 0;
	return 1;
}


Bool 	find_full_key(u_klein rop, u_klein const kTilde, u_klein const goodCouples[GOOD_COUPLES_NB][4])
{
	u_klein 	testKey, testKeyInitValue, tmpCipher;
	Key 		keys;
	Bool 		validKey;

	printf("start full key search\n");

	rotate_nibbles(testKeyInitValue, kTilde);
	for(long long k = 0 ; k < MAX_LONG ; k++)
	{


		u_klein_dcp(testKey, testKeyInitValue);
		fill_test_key(testKey, k);

		if ((k!=0) && !(k%100000000))
		{
			printf("\ttest number : %lld\t current u_klein : ", k);
			display_u_klein(testKey);
			printf("\n");
		}

		mix_nibbles(testKey, testKey);
		full_reverse_key_schedule(keys, testKey);

		validKey = 1;
		for(int i = 0 ; i < GOOD_COUPLES_NB ; i++)
		{
			encrypt(tmpCipher , goodCouples[i][0] , keys);
			if (u_klein_cmp(tmpCipher, goodCouples[i][2]))
			{
				validKey = 0;
				break;
			}
			encrypt(tmpCipher , goodCouples[i][1] , keys);
			if (u_klein_cmp(tmpCipher, goodCouples[i][3]))
			{
				validKey = 0;
				break;
			}
		}
		if (validKey)
		{
			u_klein_dcp(rop, keys[0]);
			return 1;
		}
	}
	return 0;
}


void 	fill_test_key(u_klein testKey, long long k)
{
	for(int i = NIBBLES_NB_DIV2 - 1 ; i >= 0 ; i--)
	{
		testKey[2 * i] = k % 16;
		k /= 16;
	}
}