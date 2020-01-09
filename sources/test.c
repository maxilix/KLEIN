#include	"../headers/klein.h"


void	display_cipher_differential(u_klein m)
{
	u_klein	d;
	u_klein	m1, m2;
	Key		keys;
	u_klein	buf1, buf2;

	init_keys(keys);
	init_d(d);
	u_klein_dcp(m1, m);
	u_klein_xor(m2, m1, d);

	for(int i = 0 ; i < ROUNDS_NB ; i++)
	{
		add_round_key(m1, m1, keys[i]);
		add_round_key(m2, m2, keys[i]);

		if(i == ROUNDS_NB - 1)
		{
			display_xor(m1, m2, "ARK");
			u_klein_dcp(buf1, m1);
			u_klein_dcp(buf2, m2);
		}
	
		sub_nibbles(m1, m1);
		sub_nibbles(m2, m2);
		display_xor(m1, m2, "SN");

		rotate_nibbles(m1, m1);
		rotate_nibbles(m2, m2);
		display_xor(m1, m2, "RN");
		
		mix_nibbles(m1, m1);
		mix_nibbles(m2, m2);
		display_xor(m1, m2, "MN");

		printf("________________________________\n");
	}
	add_round_key(m1, m1, keys[ROUNDS_NB]);
	add_round_key(m2, m2, keys[ROUNDS_NB]);
	display_xor(m1, m2, "CIPHER_DIFFERENTIAL");

	display_last_round_ktilde(buf1, buf2, keys[7]);
}


void	display_xor(u_klein const u1, u_klein const u2, char const *str)
{
	u_klein	x;

	u_klein_xor(x, u1, u2);
	printf("%s :\t", str);
	display_u_klein(x);
	printf("\n");
}


void	display_last_round_ktilde(u_klein m1, u_klein m2, u_klein const last_round_key)
{
	u_klein	k_tilde;

	unmix_nibbles(k_tilde , last_round_key);
	unrotate_nibbles(k_tilde, k_tilde);
	for(int i = 0 ; i < NIBBLES_NB_DIV2 ; i++)
		k_tilde[2 * i] = 0;

	printf("\n\nK_tilde :\t");
	display_u_klein(k_tilde);
	printf("\n\n");

	sub_nibbles(m1, m1);
	sub_nibbles(m2, m2);
	display_xor(m1, m2, "SN");

	add_round_key(m1, m1, k_tilde);
	add_round_key(m2, m2, k_tilde);
	display_xor(m1, m2, "ARK");

	rotate_nibbles(m1, m1);
	rotate_nibbles(m2, m2);
	display_xor(m1, m2, "RN");
	
	mix_nibbles(m1, m1);
	mix_nibbles(m2, m2);
	display_xor(m1, m2, "MN");
}


void	init_keys(Key keys)
{
	u_klein	master_key;

	str2u_klein(master_key, MASTER_KEY);
	key_schedule(keys, master_key);
}
