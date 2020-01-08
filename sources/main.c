#include 	"../headers/klein.h"


const unsigned char 	Sbox[16] = {0x7, 0x4, 0xa, 0x9, 0x1, 0xf, 0xb, 0x0, 0xc, 0x3, 0x2, 0x6, 0x8, 0xe, 0xd, 0x5};


int main()
{
	u_klein	m;

	srand(time(NULL));
	str2u_klein(m, "0x8DD7DDC36AB0075D");
	display_good_couple(m);

/*	u_klein	master_key;

	sevenRoundsAttack(master_key);
	display_u_klein(master_key);*/
	return 0;
}
