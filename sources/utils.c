#include 	"../klein.h"


void	u_klein_dcp(u_klein rop, u_klein const op)
{
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		rop[i] = op[i];
}


char	hex2char(Nibble const hex)
{
	if(hex > 15)
		return '\0';
	if(hex < 10)
		return hex + '0';
	return hex + 'A' - 10;
}


Nibble	char2nibble(char const c)
{
	switch(c)
	{
		case '0' :
		case '1' :
		case '2' :
		case '3' :
		case '4' :
		case '5' :
		case '6' :
		case '7' :
		case '8' :
		case '9' :
			return c - '0';
		case 'a' :
		case 'b' :
		case 'c' :
		case 'd' :
		case 'e' :
		case 'f' :
			return c - 'a' + 10;
		case 'A' :
		case 'B' :
		case 'C' :
		case 'D' :
		case 'E' :
		case 'F' :
			return c - 'A' + 10;
		default :
			printf("Error in char2nibble - wrong input\n");
			return 255;
	}
}


Bool	str2u_klein(u_klein rop, char const *str)
{
	if (str[0] != '0' || str[1] != 'x' || str[18] != '\0')
		return 0;
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		rop[i] = char2nibble(str[i + 2]);
	return 1;
}

void 	u_klein2str(char* rop, u_klein const uk)
{
	rop[0] = '0';
	rop[1] = 'x';
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		rop[i+2] = hex2char(uk[i]);
	rop[UKLEIN_STRING_LENGTH] = '\0';
}


int		u_klein_cmp(u_klein const op1, u_klein const op2)
{
	for(int i = 0 ; i < NIBBLES_NB ; i++)
	{
		if(op1[i] > op2[i])
			return 1;
		else if(op1[i] < op2[i])
			return -1;
	}
	return 0;
}


void	u_klein_xor(u_klein rop, u_klein const op1, u_klein const op2)
{
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		rop[i] = op1[i] ^ op2[i];
}
