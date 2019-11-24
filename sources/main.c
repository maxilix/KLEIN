#include 	"../headers/klein.h"



int main(int argc, char const *argv[])
{
	u_klein_64 	message;
	char 		result;

	result = set_u_klein_64(message, "0xab164f9cb31c0a91");

	print_u_klein_64(message);
	printf("\n");

	printf("%x\n", get_nibble_64(message,0));
	printf("%x\n", get_nibble_64(message,1));
	printf("%x\n", get_nibble_64(message,2));
	printf("%x\n", get_nibble_64(message,3));
	printf("%x\n", get_nibble_64(message,15));

	set_nibble_64(message , 3 , 0xe);

	print_u_klein_64(message);
	printf("\n");

	return 0;
}