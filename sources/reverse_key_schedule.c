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


Bool	reverse_round(u_klein const input, u_klein output, int round)
{
	int		i;
	u_klein	buf;

	if(!input || !output)
		return 0;

	u_klein_dcp(output, input);
	for(i = 10 ; i < 14 ; i++)
		output[i] = Sbox[output[i]];
	output[5] ^= round;
	u_klein_dcp(buf, output);
	for(i = 0 ; i < 8 ; i++)
	{
		output[i + 8] = buf[(i + 6) % 8];
		output[i] = buf[(i + 6) % 8] ^ buf[(i + 6) % 8 + 8];
	}
	return 1;
}