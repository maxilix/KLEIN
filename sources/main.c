#include 	"../headers/klein.h"



int main(int argc, char const *argv[])
{
	Key 		key;
	Nibble		nibble;

	if(argc == 2)
		key_schedule(key, argv[1]);
	else
		key_schedule(key, NULL);
	display_key(key);
	printf("\n");
	
	u_klein	master_key;
	reverse_key_schedule(master_key, key[7], 7);
	if(!u_klein_cmp(master_key, key[0]))
		printf("YAY\n");
	else
		printf(":c\n");
	return 0;
}
