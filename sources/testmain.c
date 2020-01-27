#include	"../klein.h"


const unsigned char 	Sbox[16] = {0x7, 0x4, 0xa, 0x9, 0x1, 0xf, 0xb, 0x0, 0xc, 0x3, 0x2, 0x6, 0x8, 0xe, 0xd, 0x5};


int main()
{
	u_klein	test;
/*	u_klein	masterKey;
	u_klein	d;
	Key		keys;*/

	str2u_klein(test, "0x1CC22DA116618507");
	print_u_klein(test, "test");
	/*str2u_klein(masterKey, MASTER_KEY)
	key_schedule(keys, masterKey);*/

	display_cipher_differential(test);
	return 0;

}
