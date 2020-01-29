#include 	"../klein.h"


int main()
{
	u_klein	master_key;
	init_generators();
	
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