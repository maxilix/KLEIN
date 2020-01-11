#include	"../klein.h"


const unsigned char 	Sbox[16] = {0x7, 0x4, 0xa, 0x9, 0x1, 0xf, 0xb, 0x0, 0xc, 0x3, 0x2, 0x6, 0x8, 0xe, 0xd, 0x5};


int main()
{
	u_klein	goodCouples[GOOD_COUPLES_NB][4];
	u_klein	d;

	init_d(d);
	find_good_couples(goodCouples, d);
	for(int i = 0 ; i < GOOD_COUPLES_NB ; i++)
	{
		printf("%d : ", i);
		display_u_klein(goodCouples[i][0]);
		printf("\n");
	}
	return 0;
}