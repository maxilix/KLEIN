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