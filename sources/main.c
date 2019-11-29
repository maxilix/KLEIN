#include 	"../headers/klein.h"



int main(int argc, char const *argv[])
{
	Key 		key;
	Nibble		nibble;

	if(argc == 2)
		key_schedule(key, argv[1]);
	else
		key_schedule(key, NULL);
	printf("\n");
	display_key(key);
	return 0;
}
