#include 	"../klein.h"


void 			random_u_klein(u_klein rop)
{
	unsigned long 	rd;
	int 			i,j;
	for(i=0 ; i<2 ; i++)
	{
		rd = random_kl();
		for(j=0 ; j<NIBBLES_NB_DIV2 ; j++)
			{
				rop[2*j+i] = rd % 16;
				rd /= 16;
			}
	}
}

unsigned long 	random_kl()
{
	static unsigned long 	rd;
	static Bool 			init = 0;


	if (!init)
	{
		init = 1;
		rd = time(NULL) % KNUTH_LEWIS_GENERATOR_M;
		for(int i = 0 ; i < clock()%16 ; i++)
			rd = random_kl();
	}

	rd = ( KNUTH_LEWIS_GENERATOR_A * rd + KNUTH_LEWIS_GENERATOR_C ) % KNUTH_LEWIS_GENERATOR_M;

	return (unsigned long)rd;
}