#include	"../headers/klein.h"


Bool	seven_rounds_attack(u_klein masterKey)
{
	u_klein		goodCouples[GOOD_COUPLES_NB][4];
	u_klein		d;
	u_klein		kTilde;
	int			cntError, i;

	init_d(d);


	////////////////////////////////////////////////////////////
	//if(!find_good_couples(goodCouples, d))
	//	return 0;
	////////////////////////////////////////////////////////////
	str2u_klein(goodCouples[0][0], "0x9F13709593912BDD");
	str2u_klein(goodCouples[1][0], "0x5B2B253393C3D4BA");
	str2u_klein(goodCouples[2][0], "0x098AEA5D7C69465F");
	str2u_klein(goodCouples[3][0], "0xE25AD55EAF1307FE");
	str2u_klein(goodCouples[4][0], "0xA23EAD6BA128928B");
	str2u_klein(goodCouples[5][0], "0x193203E283C4857B");
	str2u_klein(goodCouples[6][0], "0xD77D5B058E870CBF");
	str2u_klein(goodCouples[7][0], "0x4982C8219FCD6992");
	for(i = 0 ; i < 8 ; i++)
	{
		u_klein_xor(goodCouples[i][1], goodCouples[i][0], d);
		oracle(goodCouples[i][2],goodCouples[i][0]);
		oracle(goodCouples[i][3],goodCouples[i][1]);
	}



	////////////////////////////////////////////////////////////		
	str2u_klein(kTilde, "0x0000000000000000");				// Expected kTilde : 0x6EF8404546460E97
	for(long long k = 3892668135 ; k < 3892668136 ; k++)	// MAX_LONG ; k++) // test until 0x0A080A0E050F0800 = 2830000000‬
	{
		halfkey(kTilde, k);

		cntError = 0; i = -1;
		while(cntError <= ERROR_THRESHOLD && ++i < GOOD_COUPLES_NB)
			if(!verify_kTilde(kTilde, goodCouples[i]))
				cntError++;
		if(cntError <= ERROR_THRESHOLD)
		{
			printf("Good k tilde found : ");
			display_u_klein(kTilde);
			printf("\n");
			if(find_full_key(masterKey, kTilde, goodCouples))
				return 1;
			printf("Unsuccessful\n");
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


Bool	find_good_couples(u_klein goodCouples[GOOD_COUPLES_NB][4], u_klein const d)
{
	// si bon fichier existe, lire le fichier pour remplir le tableau goodCoules
	// sinon brute force sur la recherche de couple puis ecriture fichier, puis remplissage tableau !
	u_klein		m1, m2, c1, c2;
	u_klein		tmp, cipherDifferential;
	int			cnt, i;
	long long 	nbTest;
	Bool		valid;

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
		for(i = 0 ; i < NIBBLES_NB_DIV2 ; i++)
			if(tmp[2 * i])
			{
				valid = 0;
				break;
			}
		if(valid)
		{
			u_klein_dcp(goodCouples[cnt][0], m1);
			u_klein_dcp(goodCouples[cnt][1], m2);
			u_klein_dcp(goodCouples[cnt][2], c1);
			u_klein_dcp(goodCouples[cnt][3], c2);
			cnt++;
			printf("\nJ'en ai trouvé un : ");
			display_u_klein(m1);
			printf("\n");
		}
		
		if (!(nbTest%100000000))
		{
			printf("nombre de Test : %lld\n", nbTest);
		}

	}
	return 1;
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

	rotate_nibbles(testKeyInitValue, kTilde);
	for(long long k = 0 ; k < MAX_LONG ; k++)
	{
		u_klein_dcp(testKey, testKeyInitValue);
		fill_test_key(testKey, k);
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