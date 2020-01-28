#include	"../klein.h"


const unsigned char 	Sbox[16] = {0x7, 0x4, 0xa, 0x9, 0x1, 0xf, 0xb, 0x0, 0xc, 0x3, 0x2, 0x6, 0x8, 0xe, 0xd, 0x5};


/*
int main(int argc, char const *argv[])
{
	int			cnt;
	u_klein		m1, m2;
	u_klein		d;
	long long 	compteurTEST = 0;

	init_d(d);
	str2u_klein(m1, "0x5AC6B805049F747A");
	cnt = 0;
	for(long long k = 0 ; k < MAX_LONG ; k++)
	{
		compteurTEST++;
		if(!(compteurTEST%100000000))
			printf("\tnombre de test : %lld\n",compteurTEST);

		if(k == MAX_LONG_DIV2 && cnt <= 1)
		{
			printf("\tArret car k grand et cnt <= 1\n");
			break;
		}
		if (cnt == 4)
		{
			printf("\tArret car cnt = 4\n");
			break;
		}
		neutral_byte_modification(m1, k);
		u_klein_xor(m2, m1, d);
		if(verify_good_couple_condition(m1, m2))// && add_good_couple(goodCouples, m1, m2, index + cnt))
		{
			print_u_klein(m1,"\t Un nouveau : ");
			cnt++;
		}
	}
	if(cnt == 4)
		printf("\tWahou ! On en a chopé 4 :3\n");
	return 0;
}
*/

/*
int main()
{
	u_klein	test;
	//u_klein	masterKey;
	//u_klein	d;
	//Key		keys;

	str2u_klein(test, "0x5AC6B805049F747A");
	//print_u_klein(test, "test");
	//str2u_klein(masterKey, MASTER_KEY)
	//key_schedule(keys, masterKey);

	display_cipher_differential(test);
	return 0;

}*/




/*
int main()
{
	u_klein				m1,m2,d;
	//long long 			cnt = 0;
	unsigned long long 	uk, dcpuk;
	Bool 				found = 0;

	init_d(d);
	genarator_init();


	uk = 0;
	while(!found)
	{
		uk++;
		if (!(uk%100000000))
			printf("test number : %lld\n", uk);
		//dcpuk = uk;
		//for(int j=0 ; j<NIBBLES_NB ; j++)
		//{
		//	m1[j] = dcpuk % 16;
		//	dcpuk /= 16;
		//}
		random_u_klein_haynes(m1);
		u_klein_xor(m2,m1,d);
		if (verify_good_couple_condition_cheating(m1,m2))
		{
			print_u_klein(m1, "\tone found");
			found = 1;
		}
	}
	
}

*/