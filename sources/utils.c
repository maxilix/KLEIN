#include 	"../headers/klein.h"


void	u_klein_dcp(u_klein_64 a1, u_klein_64 a2)
{
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		a1[i] = a2[i];
}


char	hex2char(Nibble hex)
{
	if(hex < 10)
		return hex + '0';
	return hex + 'A' - 10;
}