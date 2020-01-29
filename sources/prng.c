#include 	"../klein.h"

//static unsigned long 		random_knuthlewis();
static unsigned long long 	random_haynes();

void 	init_generators()
{
	srand(time(NULL));

	//random_knuthlewis();
	random_haynes();
}


void 	random_u_klein_rand(u_klein rop)
{
	long 			rd;
	int 			i,j;

	for(i=0 ; i<4 ; i++)
	{
		rd = rand();
		rd /= 256; // remove 8 less bits
		for(j=0 ; j<NIBBLES_NB_DIV4 ; j++)
		{
			rop[4*j+i] = rd % 16;
			rd /= 16;
		}
	}
}


/*void 	random_u_klein_knuthlewis(u_klein rop)
{
	unsigned long 	rd;
	int 			i,j;
	for(i=0 ; i<2 ; i++)
	{
		rd = random_knuthlewis();
		for(j=0 ; j<NIBBLES_NB_DIV2 ; j++)
		{
			rop[2*j+i] = rd % 16;
			rd /= 16;
		}
	}
}*/

void 	random_u_klein_haynes(u_klein rop)
{
	unsigned long long 	rd;
	int 				i,j;
	for(i=0 ; i<2 ; i++)
	{
		rd = random_haynes();
		rd /= MAX_LONG; // remove 32 less bits
		for(j=0 ; j<NIBBLES_NB_DIV2 ; j++)
		{
			rop[2*j+i] = rd % 16;
			rd /= 16;
		}
	}
}



/*static unsigned long 		random_knuthlewis()
{
	static unsigned long 	rd;
	static Bool 			init = 0;


	if (!init)
	{
		init = 1;
		rd = rand();
		printf("knuth lewis generator seed : %ld\n",rd);
	}

	rd = ( KNUTH_LEWIS_GENERATOR_A * rd + KNUTH_LEWIS_GENERATOR_C ) % KNUTH_LEWIS_GENERATOR_M;

	return (unsigned long)rd;
}*/


static unsigned long long 	random_haynes()
{
	static unsigned long long 	rd;
	static Bool 				init = 0;


	if (!init)
	{
		init = 1;
		rd = rand();
		printf("haynes generator seed : %lld\n",rd);
	}

	rd = (unsigned long long)( HAYNES_GENERATOR_A * rd + HAYNES_GENERATOR_C);

	return rd;
}