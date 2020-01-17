#include	"../klein.h"


Bool	verify_good_couple_condition_cheating(u_klein const m1, u_klein const m2)
{
	static Key		keys = NULL;
	static u_klein	master_key;
	u_klein			c1, c2, cipherDifferential;

	if(!keys)
	{
		str2u_klein(master_key, MASTER_KEY);
		key_schedule(keys, master_key);
	}

	u_klein_dcp(c1, m1);
	u_klein_dcp(c2, m2);
	for(int i = 0 ; i < ROUNDS_NB ; i++)
	{
		encrypt_round(c1, keys[i]);
		encrypt_round(c2, keys[i]);
		u_klein_xor(cipherDifferential, c1, c2);
		for(int j = 0 ; j < NIBBLES_NB_DIV2 ; j++) 
			if(cipherDifferential[2 * i])
				return 0;
	}
	return 1;
}