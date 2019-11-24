#include 	"../headers/klein.h"

	//   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18
	//   0  x  f  f  f  f  f  f  f  f  f  f  f  f  f  f  f  f \0


char 		set_u_klein_64(u_klein_64 rop, char* str)
{
	if (str[0] != '0' || str[1] != 'x' || str[18] != '\0')
		return 0;

	for (int i = 0 ; i < 8 ; i++)
		rop[i] = 0;

	for (int i = 0 ; i < 16 ; i++)
		switch(str[i+2])
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
				rop[i/2] += ((i%2)? 1:16)*(str[i+2]-'0');
				break;
			case 'a' :
			case 'A' :
				rop[i/2] += ((i%2)? 1:16)*0xa;
				break;
			case 'b' :
			case 'B' :
				rop[i/2] += ((i%2)? 1:16)*0xb;
				break;
			case 'c' :
			case 'C' :
				rop[i/2] += ((i%2)? 1:16)*0xc;
				break;
			case 'd' :
			case 'D' :
				rop[i/2] += ((i%2)? 1:16)*0xd;
				break;
			case 'e' :
			case 'E' :
				rop[i/2] += ((i%2)? 1:16)*0xe;
				break;
			case 'f' :
			case 'F' :
				rop[i/2] += ((i%2)? 1:16)*0xf;
				break;
			default :
				return 0;
		}
	return 1;
}


void 	print_u_klein_64(u_klein_64 op)
{
	printf("0x");
	for (int i = 0; i < 8; i++)
		printf("%x", op[i]);
}


char 	set_nibble_64(u_klein_64 op , char i , char nibble)
{
	if (i<0 || i>15 || nibble<0x0 || nibble>0xf)
		return 0;

	if (i%2)
		op[i/2] = 16*get_nibble_64(op , i-1) + nibble;
	else
		op[i/2] = 16*nibble + get_nibble_64(op , i+1);
	return 1;
}


char 	get_nibble_64(u_klein_64 op , char i)
{
	unsigned char 	byte;

	byte = op[i/2];
	return (i%2)? byte%16 : byte/16;
}
