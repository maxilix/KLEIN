#include	"../headers/klein.h"


int		sevenRoundsAttack(u_klein master_key)
{
	u_klein	good_couples[8][2];
	u_klein	d;
	u_klein	k_tilde, master_key;
	int		cntError, i;

	init_d(d);
	if(!findGoodCouples(good_couples, d))
		return 0;
	for(unsigned long k = 0 ; k < ULONG_MAX ; k++)
	{
		halfkey(k_tilde, k);
		cntError = 0; i = -1;
		while(cntError < 2 && ++i < 8)
			if(!verify_k_tilde(i))
				cntError++;
		if(cntError < 2)
			if(findFullKey(master_key, k_tilde))
				return 1;
	}
	return 0;
}


void	init_d(u_klein d)
{
	d[0] = 0;
	d[1] = 1;
	for(int i = 0 ; i < 16 ; i++)
		d[i] = 0;
}


int		findGoodCouples(const u_klein d, u_klein good_couples[8][2])
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
		k /= 256;
	}
}
