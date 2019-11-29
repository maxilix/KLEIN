#include	"../headers/klein.h"


//unsigned char 	*SBox = {0x7, 0x4, 0xa, 0x9, 0x1, 0xf, 0xb, 0x0, 0xc, 0x3, 0x2, 0x6, 0x8, 0xe, 0xd, 0x5};
unsigned char 	*SBox = {7, 4, 10, 9, 1, 15, 11, 0, 12, 3, 2, 6, 8, 14, 13, 5};

void	key_schedule(Key key, u_klein_64 input_key)
{
	u_klein_64	master_key;

	if(!input_key)
		generate_master_key(master_key);
	else
		u_klein_dcp(master_key, input_key);

	u_klein_dcp(key[0], master_key);
	for(int i = 0 ; i < ROUNDS_NB ; i++)
		derive_new_subkey(key[i], key[i + 1], i + 1);
}


void	generate_master_key(u_klein_64 master_key)
{
	srand(15);
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		master_key[i] = rand() % 16;	// Bias with rand ?
}


void	derive_new_subkey(u_klein_64 input, u_klein_64 output, int round)
{
	int	i;


	for(i = 0 ; i < 8 ; i++)		// LS and XOR
	{
		output[i] = input[(i + 2) % 8 + 8];
		output[i + 8] = (input[(i + 2) % 8 + 8]) ^ (input[(i + 2) % 8]);
	}
	output[5] ^= round;// Change if KLEIN96
	for(i = 10 ; i < 14 ; i++)
		output[i] = Sbox[output[i]];
}