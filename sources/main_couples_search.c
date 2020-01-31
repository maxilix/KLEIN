#include	"../klein.h"
#include 	<pthread.h>
#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<time.h>
#include 	<unistd.h>

#define 	_REENTRANT
#define 	THREAD_NB 		2
#define 	COUPLES_NB 		5

FILE* 			fd;
u_klein 		d;
int 			found;

void u_klein2str(char* rop, u_klein uk)
{
	rop[0] = '0';
	rop[1] = 'x';
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		rop[i+2] = hex2char(uk[i]);
	rop[UKLEIN_STRING_LENGTH] = '\0';
}
	


void* search(void * arg)
{
	int 			id = (int) arg;
	char 			str[UKLEIN_STRING_LENGTH+1];
	u_klein			m1, m2;

	printf("start thread %d\n",id);

	while(found < COUPLES_NB)
	{
		random_u_klein_haynes(m1);
		u_klein_xor(m2, m1, d);

		if(verify_good_couple_condition(m1, m2))
		{
			u_klein2str(str, m1);
			printf("thread %d : %s\n", id , str);
			fprintf(fd,"0x%s\n",str);
			found++;
		}
	}
}


int main()
{
	char 			filename[UKLEIN_STRING_LENGTH + 27];
    pthread_t 		thread[THREAD_NB];
	init_d(d);
	init_generators();
	found = 0;

	printf("%d couples search without cheating on %d rounds with %d threads.\n", COUPLES_NB , ROUNDS_NB , THREAD_NB);

#if ROUNDS_NB == 7
	sprintf(filename, "couples/seven_rounds/%s.txt", MASTER_KEY);
#elif ROUNDS_NB == 8
	sprintf(filename, "couples/eight_rounds/%s.txt", MASTER_KEY);
#else
	printf("Erreur ROUNDS_NB\n");
	return 1;
#endif
	printf("filename to save couples : %s\n", filename);
	fd = fopen(filename, "w");

	for(int i = 0 ; i < THREAD_NB ; i++)
		pthread_create(thread+i, NULL, search, (void*)i);
	for(int i = 0 ; i < THREAD_NB ; i++)
		pthread_join(thread[i], NULL);

	fclose(fd);
	return 0;
}

