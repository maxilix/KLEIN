#include	"../headers/klein.h"


void	add_round_key(u_klein rop , u_klein op , u_klein roundKey)
{
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		rop[i] = op[i] ^ roundKey[i];
}


void 	sub_nibbles(u_klein rop , u_klein op)
{
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		rop[i] = Sbox[op[i]];
}


void 	rotate_nibbles(u_klein rop , u_klein op)
{
	Nibble 	savedNibbles[4] = {op[0], op[1], op[2], op[3]};

	for(int i = 0 ; i < NIBBLES_NB-4 ; i++)
		rop[i]=op[i+4];
	rop[NIBBLES_NB-4] = savedNibbles[0];
	rop[NIBBLES_NB-3] = savedNibbles[1];
	rop[NIBBLES_NB-2] = savedNibbles[2];
	rop[NIBBLES_NB-1] = savedNibbles[3];

}

void 	unrotate_nibbles(u_klein rop , u_klein op)
{
	Nibble 	savedNibbles[4] = {op[NIBBLES_NB-4], op[NIBBLES_NB-3], op[NIBBLES_NB-2], op[NIBBLES_NB-1]};

	for(int i = NIBBLES_NB-1 ; i >= 0 ; i--)
		rop[i]=op[i-4];
	rop[0] = savedNibbles[0];
	rop[1] = savedNibbles[1];
	rop[2] = savedNibbles[2];
	rop[3] = savedNibbles[3];
}


void 	mix_nibbles(u_klein rop , u_klein op)
{
	unsigned char 	op_left[NIBBLES_NB/4];
	unsigned char 	op_right[NIBBLES_NB/4];
	unsigned char 	rop_left[NIBBLES_NB/4];
	unsigned char 	rop_right[NIBBLES_NB/4];

	for(int i = 0 ; i < NIBBLES_NB/4 ; i++)
	{
		op_left[i]  = 16*op[2*i]              + op[2*i+1];
		op_right[i] = 16*op[2*i+NIBBLES_NB/2] + op[2*i+1+NIBBLES_NB/2];
	}

	rop_left[0] = mul2(op_left[0]) ^ mul3(op_left[1]) ^      op_left[2]  ^      op_left[3] ;
	rop_left[1] =      op_left[0]  ^ mul2(op_left[1]) ^ mul3(op_left[2]) ^      op_left[3] ;
	rop_left[2] =      op_left[0]  ^      op_left[1]  ^ mul2(op_left[2]) ^ mul3(op_left[3]);
	rop_left[3] = mul3(op_left[0]) ^      op_left[1]  ^      op_left[2]  ^ mul2(op_left[3]);

	rop_right[0] = mul2(op_right[0]) ^ mul3(op_right[1]) ^      op_right[2]  ^      op_right[3] ;
	rop_right[1] =      op_right[0]  ^ mul2(op_right[1]) ^ mul3(op_right[2]) ^      op_right[3] ;
	rop_right[2] =      op_right[0]  ^      op_right[1]  ^ mul2(op_right[2]) ^ mul3(op_right[3]);
	rop_right[3] = mul3(op_right[0]) ^      op_right[1]  ^      op_right[2]  ^ mul2(op_right[3]);

	for(int i = 0 ; i < NIBBLES_NB/4 ; i++)
	{
		rop[2*i] 					= rop_left[i]/16;
		rop[2*i + 1] 				= rop_left[i]%16;
		rop[2*i + NIBBLES_NB/2] 	= rop_right[i]/16;
		rop[2*i + 1 + NIBBLES_NB/2] = rop_right[i]%16;
	}
}

void 	unmix_nibbles(u_klein rop , u_klein op)
{
	unsigned char 	op_left[NIBBLES_NB/4];
	unsigned char 	op_right[NIBBLES_NB/4];
	unsigned char 	rop_left[NIBBLES_NB/4];
	unsigned char 	rop_right[NIBBLES_NB/4];

	for(int i = 0 ; i < NIBBLES_NB/4 ; i++)
	{
		op_left[i]  = 16*op[2*i]              + op[2*i+1];
		op_right[i] = 16*op[2*i+NIBBLES_NB/2] + op[2*i+1+NIBBLES_NB/2];
	}

	rop_left[0] = mul14(op_left[0]) ^ mul11(op_left[1]) ^ mul13(op_left[2]) ^  mul9(op_left[3]);
	rop_left[1] =  mul9(op_left[0]) ^ mul14(op_left[1]) ^ mul11(op_left[2]) ^ mul13(op_left[3]);
	rop_left[2] = mul13(op_left[0]) ^  mul9(op_left[1]) ^ mul14(op_left[2]) ^ mul11(op_left[3]);
	rop_left[3] = mul11(op_left[0]) ^ mul13(op_left[1]) ^  mul9(op_left[2]) ^ mul14(op_left[3]);

	rop_right[0] = mul14(op_right[0]) ^ mul11(op_right[1]) ^ mul13(op_right[2]) ^  mul9(op_right[3]);
	rop_right[1] =  mul9(op_right[0]) ^ mul14(op_right[1]) ^ mul11(op_right[2]) ^ mul13(op_right[3]);
	rop_right[2] = mul13(op_right[0]) ^  mul9(op_right[1]) ^ mul14(op_right[2]) ^ mul11(op_right[3]);
	rop_right[3] = mul11(op_right[0]) ^ mul13(op_right[1]) ^  mul9(op_right[2]) ^ mul14(op_right[3]);

	for(int i = 0 ; i < NIBBLES_NB/4 ; i++)
	{
		rop[2*i] 					= rop_left[i]/16;
		rop[2*i + 1] 				= rop_left[i]%16;
		rop[2*i + NIBBLES_NB/2] 	= rop_right[i]/16;
		rop[2*i + 1 + NIBBLES_NB/2] = rop_right[i]%16;
	}
}

unsigned char 	mul2(unsigned char op)
{
	int 	rop;
	rop = (int)op * 2;
	if (rop>=0xff)
		rop ^= 0x11b;
	return (unsigned char)rop;
}

unsigned char 	mul3(unsigned char op)
{
	return mul2(op)^op;
}

unsigned char 	mul9(unsigned char op)
{
	return mul2(mul2(mul2(op)))^op;
}

unsigned char 	mul11(unsigned char op)
{
	return mul2(mul2(mul2(op))^op)^op;
}

unsigned char 	mul13(unsigned char op)
{
	return mul2(mul2(mul2(op)^op))^op;
}

unsigned char 	mul14(unsigned char op)
{
	return mul2(mul2(mul2(op)^op)^op);
}



void	encrypt(u_klein cipher , u_klein plain , Key key)
{/*
	u_klein 	temp;
	u_klein_dcp(cipher, plain);

	for(int i = 0 ; i < ROUNDS_NB ; i++)
	{
		add_round_key(temp , cipher , key[i]);
		u_klein_dcp(cipher, temp);
		sub_nibbles(temp , cipher);
		u_klein_dcp(cipher, temp);
		rotate_nibbles(temp , cipher);
		u_klein_dcp(cipher, temp);
		mix_nibbles(temp , cipher);
		u_klein_dcp(cipher, temp);
	}
	add_round_key(temp , cipher , key[ROUNDS_NB]);
	u_klein_dcp(cipher, temp);*/





	u_klein_dcp(cipher, plain);

	for(int i = 0 ; i < ROUNDS_NB ; i++)
	{
		add_round_key(cipher , cipher , key[i]);
		sub_nibbles(cipher , cipher);
		rotate_nibbles(cipher , cipher);
		mix_nibbles(cipher , cipher);
	}
	add_round_key(cipher , cipher , key[ROUNDS_NB]);

}


void	decrypt(u_klein deciphered , u_klein cipher , Key key)
{/*
	u_klein 	temp;
	u_klein_dcp(deciphered, cipher);

	add_round_key(temp , deciphered , key[ROUNDS_NB]);
	u_klein_dcp(deciphered, temp);

	for(int i = ROUNDS_NB-1 ; i >= 0 ; i--)
	{
		unmix_nibbles(temp , deciphered);
		u_klein_dcp(deciphered, temp);
		unrotate_nibbles(temp , deciphered);
		u_klein_dcp(deciphered, temp);
		sub_nibbles(temp , deciphered);
		u_klein_dcp(deciphered, temp);
		add_round_key(temp , deciphered , key[i]);
		u_klein_dcp(deciphered, temp);
	}*/




	u_klein_dcp(deciphered, cipher);

	add_round_key(deciphered , deciphered , key[ROUNDS_NB]);

	for(int i = ROUNDS_NB-1 ; i >= 0 ; i--)
	{
		unmix_nibbles(deciphered , deciphered);
		unrotate_nibbles(deciphered , deciphered);
		sub_nibbles(deciphered , deciphered);
		add_round_key(deciphered , deciphered , key[i]);
	}

}
