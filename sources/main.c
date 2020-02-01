#include 	"../klein.h"


int main()
{
	u_klein		master_key_found;
	Bool 		result;

	init_generators();

#if ROUNDS_NB == 7
	result = seven_rounds_attack(master_key_found);
#elif ROUNDS_NB == 8
	result = eight_rounds_attack(master_key_found);
#else
	printf("Error ROUNDS_NB\n");
	return 0;
#endif

	if(result)
		print_u_klein(master_key_found, "Attack completed\nThe master key is");
	else
		printf("Attack failed\n");
	return 0;
}