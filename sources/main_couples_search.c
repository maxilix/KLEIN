#include	"../klein.h"
#include 	<pthread.h>
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<time.h>
#include 	<unistd.h>

#define 	_REENTRANT

FILE* 			fd;
u_klein 		d;

void u_klein2str(char* rop, u_klein uk)
{
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		rop[i] = hex2char(uk[i]);
	rop[UKLEIN_STRING_LENGTH] = '\0';
}
	


void* search(void * arg)
{
	int 			id = (int) arg;
	char 			str[UKLEIN_STRING_LENGTH+1];
	u_klein			m1, m2;

	printf("start thread %d\n",id);

	while(1)
	{
		random_u_klein_haynes(m1);
		u_klein_xor(m2, m1, d);

		if(verify_good_couple_condition(m1, m2))
		{
			printf("New\n");
			u_klein2str(str, m1);
			fprintf(fd,"thread %d : %s\n",id,str);
		}
	}
}


int main()
{
	char 			filename[UKLEIN_STRING_LENGTH + 27];
    pthread_t 		thread[2];
	init_d(d);
	init_generators();


#if ROUNDS_NB == 7
	sprintf(filename, "couples/seven_rounds/%s.txt", MASTER_KEY);
#elif ROUNDS_NB == 8
	sprintf(filename, "couples/eight_rounds/%s.txt", MASTER_KEY);
#else
	printf("Erreur ROUNDS_NB\n");
	return 1;
#endif
	printf("FN : %s\n", filename);
	fd = fopen(filename, "w");

	for(int i = 0 ; i < 2 ; i++)
		pthread_create(thread+i, NULL, search, (void*)i);

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);


	return 0;
}

