#include 	"../headers/klein.h"



int main(int argc, char const *argv[])
{
	u_klein_64 	message;
	char 		result;

	result = set_u_klein_64(message, "0xab164f9cb31c0a91");


	printf("%d\n", result);

	for (int i = 0; i < 8; i++)
		printf("%x", message[i]);
	printf("\n");


	return 0;
}