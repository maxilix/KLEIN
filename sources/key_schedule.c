#include	"../headers/klein.h"


void	key_schedule(Key key, u_klein const input_master_key)
{
	u_klein_dcp(key[0], input_master_key);
	for(int i = 0 ; i < ROUNDS_NB ; i++)
		derive_new_subkey(key[i], key[i + 1], i + 1);
}


void	init_keys(Key keys)
{
	u_klein	master_key;

	str2u_klein(master_key, MASTER_KEY);
	key_schedule(keys, master_key);
}


void	random_master_key(u_klein master_key)
{
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		master_key[i] = rand() % 16;
}


void	derive_new_subkey(u_klein const input, u_klein output, int round)
{
	int	i;


	for(i = 0 ; i < 8 ; i++)		// LS and XOR
	{
		output[i] = input[(i + 2) % 8 + 8];
		output[i + 8] = (input[(i + 2) % 8 + 8]) ^ (input[(i + 2) % 8]);
	}
	output[5] ^= round;
	for(i = 10 ; i < 14 ; i++)
		output[i] = Sbox[output[i]];
}