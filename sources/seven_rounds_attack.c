#include	"../headers/klein.h"


Bool	sevenRoundsAttack(u_klein master_key)
{
	u_klein	good_couples[GOOD_COUPLES_NB][4];
	u_klein	d;
	u_klein	k_tilde;
	int		cntError, i;
	clock_t	t_start;		// clock

	init_d(d);
	t_start = clock();		// clock
	if(!findGoodCouples(good_couples, d))
		return 0;
	printf("Good couples found in %ld ticks ! \n", clock() - t_start);		// clock
	for(long long k = 0 ; k < MAX_LONG ; k++)
	{
		halfkey(k_tilde, k);
		cntError = 0; i = -1;
		while(cntError <= ERROR_THRESHOLD && ++i < GOOD_COUPLES_NB)
			if(!verify_k_tilde(k_tilde, good_couples[i]))
				cntError++;
		if(cntError <= ERROR_THRESHOLD)
		{
			printf("Good k_tilde found !\n");
			t_start = clock();			// clock
			if(findFullKey(master_key, k_tilde, good_couples))
				return 1;
			printf("Unsuccessful bruteforce in %ld :c\n", clock() - t_start);	// clock
		}
	}
	return 0;
}


void	init_d(u_klein d)
{
	d[0] = 0;
	d[1] = 0xb;
	for(int i = 2 ; i < NIBBLES_NB ; i++)
		d[i] = 0;
}


Bool	findGoodCouples(u_klein good_couples[GOOD_COUPLES_NB][4], u_klein const d)
{
	u_klein	m1, m2, c1, c2;
	u_klein	tmp, cipherDifferential;
	int		cnt, i;
	Bool	valid;

	cnt = 0;
	while(cnt < GOOD_COUPLES_NB)
	{
		for(i = 0 ; i < NIBBLES_NB ; i++)
		{
			m1[i] = rand() % 16;
			m2[i] = m1[i] ^ d[i];
		}
		oracle(c1, m1);
		oracle(c2, m2);
		u_klein_xor(cipherDifferential, c1, c2);
		unmix_nibbles(tmp, cipherDifferential);
		valid = 1;
		for(i = 0 ; i < 8 ; i++)			// MACRO
			if(tmp[2 * i])
			{
				valid = 0;
				break;
			}
		if(valid)
		{
			u_klein_dcp(good_couples[cnt][0], m1);
			u_klein_dcp(good_couples[cnt][1], m2);
			u_klein_dcp(good_couples[cnt][2], c1);
			u_klein_dcp(good_couples[cnt][3], c2);
			cnt++;
			printf("J'en ai trouvé un !\t\t");
			display_u_klein(m1);
			printf("\n\n");
		}
	}
	return 1;
}


void	halfkey(u_klein k_tilde, long long k)
{
	for(int i = 7 ; i >= 0 ; i--)
	{
		k_tilde[2 * i + 1] = k % 16;
		k /= 16;
	}
}


Bool 	verify_k_tilde(u_klein const k_tilde, u_klein const goodCouples[4])
{
	u_klein 	cipherDifferential, tmp;
	
	u_klein_xor(cipherDifferential, goodCouples[2], goodCouples[3]);
	unmix_nibbles(tmp , cipherDifferential);
	unrotate_nibbles(tmp , tmp);
	add_round_key(tmp , tmp , k_tilde);
	sub_nibbles(tmp , tmp);
	unmix_nibbles(tmp , tmp);

	for(int i = 0 ; i < NIBBLES_NB/2 ; i++) ////// MARCO
		if(tmp[2 * i])
			return 0;
	return 1;
}


Bool 	findFullKey(u_klein rop, u_klein const k_tilde, u_klein const goodCouples[GOOD_COUPLES_NB][4])
{
	u_klein 	masterKey, tmpCipher;
	Key 		keys;
	Bool 		validKey;

	tildeToMaster(masterKey, k_tilde);

	for(long long k = 0 ; k < MAX_LONG ; k++)
	{
		fillMasterKey(masterKey, k);
		key_schedule(keys, masterKey);
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
			u_klein_dcp(rop, masterKey);
			return 1;
		}
	}
	return 0;
}

void 	tildeToMaster(u_klein masterKey, u_klein const k_tilde)
{
	u_klein 	k;

	rotate_nibbles(k , k_tilde);
	mix_nibbles(k , k);
	reverse_key_schedule(masterKey, k, 7);
}



void 	fillMasterKey(u_klein masterKey, long long k)
{
	for(int i = 7 ; i >= 0 ; i--)
	{
		masterKey[2 * i] = k % 16;
		k /= 16;
	}
}