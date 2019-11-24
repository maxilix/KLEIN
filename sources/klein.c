#include 	"../headers/klein.h"



char 		set_u_klein_64(u_klein_64 rop, char* str)
{
	//   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18
	//   0  x  f  f  f  f  f  f  f  f  f  f  f  f  f  f  f  f \0

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
				rop[i/2] += ((i%2)? 1:16)*10;
				break;
			case 'b' :
			case 'B' :
				rop[i/2] += ((i%2)? 1:16)*11;
				break;
			case 'c' :
			case 'C' :
				rop[i/2] += ((i%2)? 1:16)*12;
				break;
			case 'd' :
			case 'D' :
				rop[i/2] += ((i%2)? 1:16)*13;
				break;
			case 'e' :
			case 'E' :
				rop[i/2] += ((i%2)? 1:16)*14;
				break;
			case 'f' :
			case 'F' :
				rop[i/2] += ((i%2)? 1:16)*15;
				break;
			default :
				return 0;
		}
	return 1;
}

