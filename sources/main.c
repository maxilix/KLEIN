#include 	"../klein.h"


const unsigned char 	Sbox[16] = {0x7, 0x4, 0xa, 0x9, 0x1, 0xf, 0xb, 0x0, 0xc, 0x3, 0x2, 0x6, 0x8, 0xe, 0xd, 0x5};





int main()
{
	u_klein	master_key;
	Key	keys;

	srand(time(NULL));

	init_keys(keys);
	display_key(keys);
	printf("\n\n");
	
	switch(ROUNDS_NB)
	{
		case 7 :
			seven_rounds_attack(master_key);
			break;
		case 8 :
			eight_rounds_attack(master_key);
			break;
		case 12 :
			printf("HA HA ...\n");
			break;
	}

	print_u_klein(master_key, "YAY ! The master key is");
	return 0;
}



/*
int main()
{
	u_klein	master_key;
	Key	keys;

	srand(time(NULL));
	switch(ROUNDS_NB)
	{
		case 7 :
			seven_rounds_attack(master_key);
			break;
		case 8 :
			eight_rounds_attack(master_key);
			break;
		case 12 :
			printf("HA HA ...\n");
			break;
	}

	print_u_klein(master_key, "YAY ! The master key is");
	return 0;
}*/