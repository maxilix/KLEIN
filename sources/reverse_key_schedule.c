#include	"../headers/klein.h"


Bool	reverse_key_schedule(u_klein master_key, u_klein const round_key, int round)
{
	u_klein	tmp_key;

	if(!master_key || !round_key)
		return 0;
	u_klein_dcp(tmp_key, round_key);
	for(int i = round ; i > 0 ; i--)
		reverse_round(tmp_key, tmp_key, i);
	u_klein_dcp(master_key, tmp_key);
	return 1;
}


void	full_reverse_key_schedule(Key keys, u_klein const last_round_key)
{
	u_klein_dcp(keys[ROUNDS_NB], last_round_key);
	for(int i = ROUNDS_NB ; i > 0 ; i--)
		reverse_round(keys[i - 1], keys[i], i);

}


void	reverse_round(u_klein output, u_klein const input, int round)
{
	int		i, calculus_result;
	u_klein	buf;

	u_klein_dcp(output, input);
	for(i = 10 ; i < 14 ; i++)
		output[i] = Sbox[output[i]];
	output[5] ^= round;
	u_klein_dcp(buf, output);
	for(i = 0 ; i < 8 ; i++)
	{
		calculus_result = i + 6 % 8;
		output[i + 8] = buf[calculus_result];
		output[i] = buf[calculus_result] ^ buf[calculus_result + 8];
	}
}
