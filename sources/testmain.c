#include	"../klein.h"




/*
int main(int argc, char const *argv[])
{
	int			cnt;
	u_klein		m1, m2;
	u_klein		d;
	long long 	compteurTEST = 0;

	init_d(d);
	str2u_klein(m1, argv[1]);
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
		//if (cnt == 4)
		//{
		//	printf("\tArret car cnt = 4\n");
		//	break;
		//}
		neutral_byte_modification(m1, k);
		u_klein_xor(m2, m1, d);
		if(verify_good_couple_condition(m1, m2))// && add_good_couple(goodCouples, m1, m2, index + cnt))
		{
			print_u_klein(m1,"\t Un nouveau : ");
			cnt++;
		}
	}
	printf("total : %d\n",cnt);
	return 0;
}



/*
int main(int argc, char const *argv[])
{
	u_klein	test;

	str2u_klein(test, argv[1]);
	display_cipher_differential(test);
	return 0;

}


/*
int main()
{
	u_klein				m1,m2,d;
	unsigned long long 	uk;

	init_d(d);
	init_generators();


	uk = 0;
	while(1)
	{
		uk++;
		if (!(uk%100000000))
		{
			printf("test number : %lld \t\t", uk);
			display_u_klein(m1);
			printf("\n");
		}
		random_u_klein_haynes(m1);
		u_klein_xor(m2,m1,d);
		if (verify_good_couple_condition_cheating(m1,m2))
			print_u_klein(m1, "\tone found");
	}
	
}*/




int main(int argc, char const *argv[])
{
	u_klein				m;
	init_generators();
	for(int i = 0 ; i < 10000000 ; i++)
		random_u_klein_rand(m);
	print_u_klein(m,"r");



	return 0;
}

/*
int main(int argc, char const *argv[])
{
	printf("const unsigned char \tmul14table[256] = {");

	for(int i = 0 ; i < 256 ; i++)
	{
		printf("0x%2x, ",mul14(i));
		if (i==255)
		{
			printf("\b\b};\n");
			return 0;
		}
		if (i%16==15)
			printf("\n\t\t\t\t\t\t\t\t\t\t   ");
	}

	return 0;
}*/