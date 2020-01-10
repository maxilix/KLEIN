#include	"../headers/klein.h"


void	key_schedule(Key keys, u_klein const input_masterKey)
{
	u_klein_dcp(keys[0], input_masterKey);
	for(int i = 0 ; i < ROUNDS_NB ; i++)
		derive_new_subkey(keys[i], keys[i + 1], i + 1);
}


void	init_keys(Key keys)
{
	u_klein	masterKey;

	str2u_klein(masterKey, MASTER_KEY);
	key_schedule(keys, masterKey);
}


void	random_master_key(u_klein masterKey)
{
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		masterKey[i] = rand() % 16;
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