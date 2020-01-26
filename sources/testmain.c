#include	"../klein.h"


const unsigned char 	Sbox[16] = {0x7, 0x4, 0xa, 0x9, 0x1, 0xf, 0xb, 0x0, 0xc, 0x3, 0x2, 0x6, 0x8, 0xe, 0xd, 0x5};


int main()
{
	u_klein 			rd;
	unsigned long long 	t, pow;
	genarator_init();

	for (int i = 0 ; i < 10000 ; i++)
	{
		t = 0;
		pow = 1;
		random_u_klein_haynes(rd);
		for(int i = 0 ; i < NIBBLES_NB ; i++)
		{	
			t+=rd[i]*pow;
			pow*=16;
		}
		printf("%llu\n",t);

	}

	return 0;

}
