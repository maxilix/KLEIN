#include	"../klein.h"


void	add_round_key(u_klein rop , u_klein const op , u_klein const roundKey)
{
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		rop[i] = op[i] ^ roundKey[i];
}


void 	sub_nibbles(u_klein rop , u_klein const op)
{
	for(int i = 0 ; i < NIBBLES_NB ; i++)
		rop[i] = Sbox[op[i]];
}


void 	rotate_nibbles(u_klein rop , u_klein const op)
{
	Nibble 	savedNibbles[4] = {op[0], op[1], op[2], op[3]};

	for(int i = 0 ; i < NIBBLES_NB-4 ; i++)
		rop[i]=op[i+4];
	rop[NIBBLES_NB-4] = savedNibbles[0];
	rop[NIBBLES_NB-3] = savedNibbles[1];
	rop[NIBBLES_NB-2] = savedNibbles[2];
	rop[NIBBLES_NB-1] = savedNibbles[3];

}

void 	unrotate_nibbles(u_klein rop , u_klein const op)
{
	Nibble 	savedNibbles[4] = {op[NIBBLES_NB-4], op[NIBBLES_NB-3], op[NIBBLES_NB-2], op[NIBBLES_NB-1]};

	for(int i = NIBBLES_NB-1 ; i >= 0 ; i--)
		rop[i]=op[i-4];
	rop[0] = savedNibbles[0];
	rop[1] = savedNibbles[1];
	rop[2] = savedNibbles[2];
	rop[3] = savedNibbles[3];
}


void 	mix_nibbles(u_klein rop , u_klein const op)
{
	unsigned char 	opLeft[NIBBLES_NB_DIV4];
	unsigned char 	opRight[NIBBLES_NB_DIV4];
	unsigned char 	ropLeft[NIBBLES_NB_DIV4];
	unsigned char 	ropRight[NIBBLES_NB_DIV4];

	for(int i = 0 ; i < NIBBLES_NB_DIV4 ; i++)
	{
		opLeft[i]  = 16*op[2*i]              + op[2*i+1];
		opRight[i] = 16*op[2*i+NIBBLES_NB_DIV2] + op[2*i+1+NIBBLES_NB_DIV2];
	}

	ropLeft[0] = mul2table[opLeft[0]] ^ mul3table[opLeft[1]] ^           opLeft[2]  ^           opLeft[3] ;
	ropLeft[1] =           opLeft[0]  ^ mul2table[opLeft[1]] ^ mul3table[opLeft[2]] ^           opLeft[3] ;
	ropLeft[2] =           opLeft[0]  ^           opLeft[1]  ^ mul2table[opLeft[2]] ^ mul3table[opLeft[3]];
	ropLeft[3] = mul3table[opLeft[0]] ^           opLeft[1]  ^           opLeft[2]  ^ mul2table[opLeft[3]];

	ropRight[0] = mul2table[opRight[0]] ^ mul3table[opRight[1]] ^           opRight[2]  ^           opRight[3] ;
	ropRight[1] =           opRight[0]  ^ mul2table[opRight[1]] ^ mul3table[opRight[2]] ^           opRight[3] ;
	ropRight[2] =           opRight[0]  ^           opRight[1]  ^ mul2table[opRight[2]] ^ mul3table[opRight[3]];
	ropRight[3] = mul3table[opRight[0]] ^           opRight[1]  ^           opRight[2]  ^ mul2table[opRight[3]];

	for(int i = 0 ; i < NIBBLES_NB_DIV4 ; i++)
	{
		rop[2*i] 					= ropLeft[i]/16;
		rop[2*i + 1] 				= ropLeft[i]%16;
		rop[2*i + NIBBLES_NB/2] 	= ropRight[i]/16;
		rop[2*i + 1 + NIBBLES_NB/2] = ropRight[i]%16;
	}
}

void 	unmix_nibbles(u_klein rop , u_klein const op)
{
	unsigned char 	opLeft[NIBBLES_NB/4];
	unsigned char 	opRight[NIBBLES_NB/4];
	unsigned char 	ropLeft[NIBBLES_NB/4];
	unsigned char 	ropRight[NIBBLES_NB/4];

	for(int i = 0 ; i < NIBBLES_NB_DIV4 ; i++)
	{
		opLeft[i]  = 16*op[2*i]              + op[2*i+1];
		opRight[i] = 16*op[2*i+NIBBLES_NB/2] + op[2*i+1+NIBBLES_NB/2];
	}

	ropLeft[0] = mul14table[opLeft[0]] ^ mul11table[opLeft[1]] ^ mul13table[opLeft[2]] ^  mul9table[opLeft[3]];
	ropLeft[1] =  mul9table[opLeft[0]] ^ mul14table[opLeft[1]] ^ mul11table[opLeft[2]] ^ mul13table[opLeft[3]];
	ropLeft[2] = mul13table[opLeft[0]] ^  mul9table[opLeft[1]] ^ mul14table[opLeft[2]] ^ mul11table[opLeft[3]];
	ropLeft[3] = mul11table[opLeft[0]] ^ mul13table[opLeft[1]] ^  mul9table[opLeft[2]] ^ mul14table[opLeft[3]];

	ropRight[0] = mul14table[opRight[0]] ^ mul11table[opRight[1]] ^ mul13table[opRight[2]] ^  mul9table[opRight[3]];
	ropRight[1] =  mul9table[opRight[0]] ^ mul14table[opRight[1]] ^ mul11table[opRight[2]] ^ mul13table[opRight[3]];
	ropRight[2] = mul13table[opRight[0]] ^  mul9table[opRight[1]] ^ mul14table[opRight[2]] ^ mul11table[opRight[3]];
	ropRight[3] = mul11table[opRight[0]] ^ mul13table[opRight[1]] ^  mul9table[opRight[2]] ^ mul14table[opRight[3]];

	for(int i = 0 ; i < NIBBLES_NB_DIV4 ; i++)
	{
		rop[2*i] 					= ropLeft[i]/16;
		rop[2*i + 1] 				= ropLeft[i]%16;
		rop[2*i + NIBBLES_NB/2] 	= ropRight[i]/16;
		rop[2*i + 1 + NIBBLES_NB/2] = ropRight[i]%16;
	}
}

unsigned char 	mul2(unsigned char const op)
{
	int 	rop;
	rop = (int)op * 2;
	if (rop>=0xff)
		rop ^= 0x11b;
	return (unsigned char)rop;
}

unsigned char 	mul3(unsigned char const op)
{
	return mul2(op)^op;
}

unsigned char 	mul9(unsigned char const op)
{
	return mul2(mul2(mul2(op)))^op;
}

unsigned char 	mul11(unsigned char const op)
{
	return mul2(mul2(mul2(op))^op)^op;
}

unsigned char 	mul13(unsigned char const op)
{
	return mul2(mul2(mul2(op)^op))^op;
}

unsigned char 	mul14(unsigned char const op)
{
	return mul2(mul2(mul2(op)^op)^op);
}


void	encrypt_round(u_klein cipher, u_klein const roundKey)
{
	add_round_key(cipher , cipher , roundKey);
	sub_nibbles(cipher , cipher);
	rotate_nibbles(cipher , cipher);
	mix_nibbles(cipher , cipher);
}


void	encrypt(u_klein cipher , u_klein const plain , Key const key)
{
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


void	decrypt(u_klein deciphered , u_klein const cipher , Key const key)
{
	add_round_key(deciphered , cipher , key[ROUNDS_NB]);

	for(int i = ROUNDS_NB-1 ; i >= 0 ; i--)
	{
		unmix_nibbles(deciphered , deciphered);
		unrotate_nibbles(deciphered , deciphered);
		sub_nibbles(deciphered , deciphered);
		add_round_key(deciphered , deciphered , key[i]);
	}
}


void	oracle(u_klein cipher, u_klein const plain)
{
	static Bool		firstTime = 1;
	static Key		key;
	static u_klein	masterKey;

	if(firstTime)
	{
		str2u_klein(masterKey, MASTER_KEY);
		key_schedule(key, masterKey);
	}
	firstTime = 0;
	encrypt(cipher, plain, key);
}
