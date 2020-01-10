#include	"../klein.h"


Bool	reverse_key_schedule(u_klein masterKey, u_klein const roundKey, int round)
{
	if(!masterKey || !roundKey)
		return 0;
	u_klein_dcp(masterKey, roundKey);
	for(int i = round ; i > 0 ; i--)
		reverse_round(masterKey, masterKey, i);
	return 1;
}


void	full_reverse_key_schedule(Key keys, u_klein const lastRoundKey)
{
	u_klein_dcp(keys[ROUNDS_NB], lastRoundKey);
	for(int i = ROUNDS_NB ; i > 0 ; i--)
		reverse_round(keys[i - 1], keys[i], i);
}


void	reverse_round(u_klein output, u_klein const input, int round)
{
	int		i, calculusResult;
	u_klein	buf;

	u_klein_dcp(output, input);
	for(i = 10 ; i < 14 ; i++)
		output[i] = Sbox[output[i]];
	output[5] ^= round;
	u_klein_dcp(buf, output);
	for(i = 0 ; i < 8 ; i++)
	{
		calculusResult = (i + 6) % 8;
		output[i + 8] = buf[calculusResult];
		output[i] = buf[calculusResult] ^ buf[calculusResult + 8];
	}
}
