#include 	"../headers/klein.h"



int main(int argc, char const *argv[])
{
	Key 		key;
	Nibble		nibble;

	if(argc == 2)
		;// read master_key and generates key
	else
		key_schedule(key, NULL);
	for(int i = 0 ; i < 16 ; i++)
		printf("Sbox[%d] = %d\n", i, Sbox[i]);
	printf("\n");
	display_key(key);
	return 0;
}