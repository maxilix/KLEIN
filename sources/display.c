#include	"../headers/klein.h"


void	display_key(Key const key)
{
	for(int i = 0 ; i < ROUNDS_NB + 1 ; i++)
	{
		printf("K_%d : ", i);
		display_u_klein(key[i]);
		printf("%s", i % 2 == 0 ? "\t\t" : "\n");
	}
	printf("\n");
}


void	display_u_klein(u_klein const uk)
{
	for(int i = 0 ; i < NIBBLES_NB ; i++)
	{
		printf("%c", hex2char(uk[i]));
		if(i % 2 == 1 && i != NIBBLES_NB - 1)
			printf(" ");
	}
}


void	print_u_klein(u_klein const u, char *str)
{
	printf("%s :\t", str);
	display_u_klein(u);
	printf("\n");
}


void	display_xor(u_klein const u1, u_klein const u2, char const *str)
{
	u_klein	x;

	u_klein_xor(x, u1, u2);
	printf("%s :\t", str);
	display_u_klein(x);
	printf("\n");
}


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