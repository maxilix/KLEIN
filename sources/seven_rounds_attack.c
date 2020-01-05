#include	"../headers/klein.h"


int		sevenRoundsAttack(u_klein master_key)
{
	u_klein	good_couples[8][2];
	u_klein	d;
	u_klein	k_tilde, master_key;
	int		cntError, i, k;

	init_d(d);
	if(!findGoodCouples(good_couples, d))
		return 0;
	k = -1;
	do
	{
		halfkey(k_tilde, ++k);
		cntError = 0; i = -1;
		while(cntError < 2 && ++i < 8)
			if(!verify_k_tilde(k_tilde, good_couples[i]))
				cntError++;
		if(cntError < 2)
			if(findFullKey(master_key, k_tilde, good_couples))
				return 1;
	} while(k < 4294967295)
	return 0;
}


void	init_d(u_klein d)
{
	d[0] = 0;
	d[1] = 1;
	for(int i = 0 ; i < 16 ; i++)
		d[i] = 0;
}


Bool	findGoodCouples(const u_klein d, u_klein good_couples[8][2])
{
	u_klein	m1, m2, c1, c2;
	u_klein	tmp;
	int		cnt, i;
	Bool	valid;

	cnt = 0;
	while(cnt < 9)
	{
		for(i = 0 ; i < NIBBLES_NB ; i++)
		{
			m1[i] = rand() % 16;			// Gérer aléa
			m2[i] = m1[i] ^ d[i];
		}
		encrypt(c1, m1);					// Gerer fct avec Baptiste
		encrypt(c2, m2);					// Gerer fct avec Baptiste
		tmp = mixColumn-1(c1 ^ c2);			// Gerer fct avec Baptiste
		valid = 1;
		for(i = 0 ; i < 8 ; i++)			// 8 = NIBBLES_NB / 2
			if(tmp[2 * i])
			{
				valid = 0;
				break;
			}
		if(valid)
		{
			u_klein_dcp(good_couples[cnt][0], m1);
			u_klein_dcp(good_couples[cnt++][1], m2);
		}
	}
	return 1;							// Rajouter une mauvaise execution avec un gros compteur ?
}


void	halfkey(u_klein k_tilde, const unsigned long k)
{
	for(int i = 7 ; i >= 0 ; i--)
	{
		k_tilde[2 * i + 1] = k % 16;
		k /= 16;
	}
}


Bool 	verify_k_tilde(const u_klein k_tilde, const u_klein couples[4])
{
	u_klein 	cipherDifferential, tmp;
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		cipherDifferential[i] = couples[2][i] ^ couples[3][i];

	unmix_nibbles(tmp , cipherDifferential);
	unrotate_nibbles(tmp , tmp);
	add_round_key(tmp , tmp , k_tilde);
	sub_nibbles(tmp , tmp);
	unmix_nibbles(tmp , tmp);

	for(int i = 0 ; i < NIBBLES_NB/2 ; i++) ////// MARCO
		if(tmp[2 * i])
		{
			return 0;
		}
	return 1;
}


Bool 	findFullKey(u_klein rop, const u_klein k_tilde, const u_klein goodCouples[8][4])
{
	u_klein 	masterKey, tmpCipher;
	Key 		keys;
	Bool 		validKey;

	tildeToMaster(masterKey, k_tilde);

	for(long long k = 0 ; k < MAX_LONG ; k++)
	{
		fillMasterKey(masterKey,k);
		// KEY DERIVATION
		u_klein_dcp(keys[0], masterKey);
		for(int i = 0 ; i < ROUNDS_NB ; i++)
			derive_new_subkey(keys[i], keys[i + 1], i + 1);
		//////////////////
		validKey = 1;
		for(int i = 0 ; i < 8 ; i++) // Define COUPLES_NB 	8
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
			u_klein_dcp(rop , masterKey);
			return 1;
		}
	}
	return 0;
}

void 	tildeToMaster(u_klein masterKey, const u_klein k_tilde)
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