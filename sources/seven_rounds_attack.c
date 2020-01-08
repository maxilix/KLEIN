#include	"../headers/klein.h"


Bool	sevenRoundsAttack(u_klein master_key)
{
	u_klein	good_couples[GOOD_COUPLES_NB][4];
	u_klein	d;
	u_klein	k_tilde;
	int		cntError, i;
	//clock_t	t_start;		// clock

	init_d(d);


	//t_start = clock();		// clock
	////////////////////////////////////////////////////////////
	//if(!findGoodCouples(good_couples, d))
	//	return 0;
	////////////////////////////////////////////////////////////
	u_klein 	tmp;
	str2u_klein(good_couples[0][0], "0x9F13709593912BDD");
	str2u_klein(good_couples[1][0], "0x5B2B253393C3D4BA");
	str2u_klein(good_couples[2][0], "0x098AEA5D7C69465F");
	str2u_klein(good_couples[3][0], "0xE25AD55EAF1307FE");
	str2u_klein(good_couples[4][0], "0xA23EAD6BA128928B");
	str2u_klein(good_couples[5][0], "0x193203E283C4857B");
	str2u_klein(good_couples[6][0], "0xD77D5B058E870CBF");
	str2u_klein(good_couples[7][0], "0x4982C8219FCD6992");
	for(i = 0 ; i < 8 ; i++)
	{
		u_klein_xor(good_couples[i][1], good_couples[i][0], d);
		oracle(good_couples[i][2],good_couples[i][0]);
		oracle(good_couples[i][3],good_couples[i][1]);
		u_klein_xor(tmp, good_couples[i][2],good_couples[i][3]);
		unmix_nibbles(tmp,tmp);
		printf("i = %d\nm : ",i);
		display_u_klein(good_couples[i][0]);
		printf("\nxor unmix : ");
		display_u_klein(tmp);
		printf("\n\n");
	}



	////////////////////////////////////////////////////////////
	//printf("Good couples found in %ld ticks ! \n", clock() - t_start);		// clock
	str2u_klein(k_tilde, "0x0000000000000000");
	for(long long k = 3892668135 ; k < 3892668136 ; k++) //MAX_LONG ; k++) // test until 0x0A080A0E050F0800 = 2830000000‬
	{
		halfkey(k_tilde, k);

		//if(!(k%10000000))
		//{
			printf("k : ");
			display_u_klein(k_tilde);
			printf("\n");
			printf("\n");
		//}

		cntError = 0; i = -1;
		while(cntError <= ERROR_THRESHOLD && ++i < GOOD_COUPLES_NB)
			if(!verify_k_tilde(k_tilde, good_couples[i]))
				cntError++;
		if(cntError <= ERROR_THRESHOLD)
		{
			printf("Good k_tilde found : ");
			display_u_klein(k_tilde);
			printf("\n");
			//t_start = clock();			// clock
			if(findFullKey(master_key, k_tilde, good_couples))
				return 1;
			printf("Unsuccessful\n");// bruteforce in %ld :c\n", clock() - t_start);	// clock
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
	long long nbTest = 0;
	Bool	valid;

	cnt = 0;
	while(cnt < GOOD_COUPLES_NB)
	{
		nbTest++;
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
			printf("\nJ'en ai trouvé un : ");
			display_u_klein(m1);
			printf("\n\n");
		}
		
		if (!(nbTest%100000000))
		{
			printf("nombre de Test : %lld\n", nbTest);
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
	display_u_klein(tmp);
	printf("\n");
	unrotate_nibbles(tmp , tmp);
	add_round_key(tmp , tmp , k_tilde);
	sub_nibbles(tmp , tmp);
	unmix_nibbles(tmp , tmp);
	display_u_klein(tmp);
	printf("\n");

	for(int i = 0 ; i < NIBBLES_NB_DIV2 ; i++)
		if(tmp[2 * i])
		{
			printf("return 0\n\n");
			return 0;
		}
	printf("return 1\n\n");
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