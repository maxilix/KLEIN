#include	"../klein.h"
static Bool	find_good_couples(u_klein goodCouples[GOOD_COUPLES_NB][4], u_klein const d);
static Bool	extract_couples_from_file(u_klein goodCouples[GOOD_COUPLES_NB][4], u_klein const d);


Bool		eight_rounds_attack(u_klein masterKey)
{
	u_klein		goodCouples[GOOD_COUPLES_NB][4];
	u_klein		d;
	u_klein		kTilde;
	int			i, isValid;

	printf("Je rentre dans eight_rounds_attack !\n");
	init_d(d);

	if(!find_good_couples(goodCouples, d))
		return 0;

	for(i = 0 ; i < GOOD_COUPLES_NB ; i++)
	{
		u_klein_xor(goodCouples[i][1], goodCouples[i][0], d);
		oracle(goodCouples[i][2],goodCouples[i][0]);
		oracle(goodCouples[i][3],goodCouples[i][1]);
	}
		
	str2u_klein(kTilde, "0x0000000000000000");	// Expected kTilde : 0x6EF8404546460E97
	for(long long k = 0 ; k < MAX_LONG ; k++)	// test until 0x0A080A0E050F0800 = 2830000000‬
	{
		halfkey(kTilde, k);
		isValid = 1;
		for(i = 0 ; i < GOOD_COUPLES_NB ; i++)
			if(!verify_kTilde(kTilde, goodCouples[i]))
			{
				isValid = 0;
				break;
			}
		if(isValid)
		{
			print_u_klein(kTilde, "Good k_tilde found");
			if(find_full_key(masterKey, kTilde, goodCouples))
				return 1;
			printf("Unsuccessful\n");
		}
	}
	return 0;
}


static Bool	find_good_couples(u_klein goodCouples[GOOD_COUPLES_NB][4], u_klein const d)
{
	u_klein			m1, m2;
	int				cnt, i, index;
	unsigned long	rd;

	if(extract_couples_from_file(goodCouples, d))		
		return 1;
	printf("C'est parti pour la recherche des couples !\n");
	cnt = 0;
	while(cnt < GOOD_COUPLES_NB)
	{
		for(int j = 0 ; j < 2 ; j++)
		{
			rd = (unsigned long)rand();
			for(i = 0 ; i < NIBBLES_NB_DIV2 ; i++)
			{
				index = i + j * NIBBLES_NB_DIV2;
				m1[index] = rd % 16;
				rd /= 16;
				m2[index] = m1[index] ^ d[index];
			}
		}
		if(verify_good_couple_condition(m1, m2))
		{
			u_klein_dcp(goodCouples[cnt][0], m1);
			u_klein_dcp(goodCouples[cnt][1], m2);
			if(verify_good_couple(goodCouples))
				cnt += 4;
		}
	}
	return 1;
}


static Bool		extract_couples_from_file(u_klein goodCouples[GOOD_COUPLES_NB][4], u_klein const d)
{
	FILE	*fd;
	char	filename[UKLEIN_STRING_LENGTH + 27];
	char	buf[UKLEIN_STRING_LENGTH + 2];

	sprintf(filename, "couples/eight_rounds/%s.txt", MASTER_KEY);
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
	return 1;
}


Bool	verify_good_couple(u_klein goodCouples[GOOD_COUPLES_NB][4])
{
	static int	index = 0;
	int			cnt;
	u_klein		m1, m2;

	print_u_klein(m1, "Celui là vérifie la condition");
	cnt = 0;
	for(long long k = 0 ; k < MAX_LONG ; k++)
	{
		if(k == MAX_LONG_DIV2 && !cnt)
			break;
		neutral_byte_modification(m1, goodCouples[index][0], k);
		neutral_byte_modification(m2, goodCouples[index][1], k);
		if(verify_good_couple_condition(m1, m2))
		{
			add_good_couple(goodCouples, m1, m2, index + cnt);
			cnt++;
		}
	}
	if(cnt >= 4)
	{
		printf("Wahou ! On en a chopé 4 :3\n");
		return 1;
	}
	return 0;
}


void	neutral_byte_modification(u_klein rop, u_klein op, long long k)
{
	int	i;

	for(i = 0 ; i < NIBBLES_NB ; i++)
	{
		if((i + 4) % 16 < NIBBLES_NB_DIV2)
		{
			rop[i] = k % 16;
			k /= 16;
		}
		else
			rop[i] = op[i];
	}
}