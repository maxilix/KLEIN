#include	"../headers/klein.h"


const unsigned char 	Sbox[16] = {0x7, 0x4, 0xa, 0x9, 0x1, 0xf, 0xb, 0x0, 0xc, 0x3, 0x2, 0x6, 0x8, 0xe, 0xd, 0x5};



int main()
{
	Key keys;
	u_klein	master_key;

	init_keys(keys);
	display_key(keys);

	reverse_key_schedule(master_key, keys[ROUNDS_NB], ROUNDS_NB);
	printf("\n");
	display_u_klein(master_key);
	printf("\n");
	return 0;
}