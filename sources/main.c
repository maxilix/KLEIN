#include 	"../headers/klein.h"


const unsigned char 	Sbox[16] = {0x7, 0x4, 0xa, 0x9, 0x1, 0xf, 0xb, 0x0, 0xc, 0x3, 0x2, 0x6, 0x8, 0xe, 0xd, 0x5};


int main()
{
	Key 		keys;


	srand(time(NULL));
	u_klein	master_key;
	u_klein k_tilde;



	sevenRoundsAttack(master_key);
	/*
	str2u_klein(master_key, MASTER_KEY);
	printf("Master : ");
	display_u_klein(master_key);
	printf("\n");

	key_schedule(keys, master_key);

	display_key(keys);

	unmix_nibbles(k_tilde , keys[7]);
	unrotate_nibbles(k_tilde, k_tilde);

	printf("k_tilde : ");
	display_u_klein(k_tilde);
	printf("\n");*/


	return 0;
}


