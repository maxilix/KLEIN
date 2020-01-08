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


void	display_good_couple(u_klein const m1)
{
	u_klein	d;
	u_klein	m2, c1, c2;
	u_klein	cipherDifferential;
	u_klein	verif;

	init_d(d);
	u_klein_xor(m2, m1, d);
	oracle(c1, m1);
	oracle(c2, m2);
	u_klein_xor(cipherDifferential, c1, c2);
	unmix_nibbles(verif, cipherDifferential);

	printf("m1 = ");
	display_u_klein(m1);
	printf("\nm2 = ");
	display_u_klein(m2);
	getchar();
	printf("\nUnmixNibbles(c1 XOR c2) = ");
	display_u_klein(verif);
	printf("\n");
}