#include 	"../headers/klein.h"


const unsigned char 	Sbox[16] = {0x7, 0x4, 0xa, 0x9, 0x1, 0xf, 0xb, 0x0, 0xc, 0x3, 0x2, 0x6, 0x8, 0xe, 0xd, 0x5};


int main()
{
	u_klein	master_key;
	u_klein	answer;
	Key	keys;

	srand(time(NULL));
	init_keys(keys);
	display_key(keys);
	printf("\n\n");
	sevenRoundsAttack(master_key);
	str2u_klein(answer, MASTER_KEY);
	if(!u_klein_cmp(master_key, answer))
		printf("YAY !!!\n");
	else
		printf(":c\n");
	return 0;
}


