#ifndef 	__KLEIN_H__
#define 	__KLEIN_H__


#include 	<stdio.h>
#include 	<stdlib.h>



//sunsigned char 	Sbox[16] = {0x7, 0x4, 0xa, 0x9, 0x1, 0xf, 0xb, 0x0, 0xc, 0x3, 0x2, 0x6, 0x8, 0xe, 0xd, 0x5};


//   64 BITS   //////////////////////////////////////////////
typedef unsigned char	u_klein_64[8];

char 	encryption_64(u_klein_64 cipher , u_klein_64 message , u_klein_64 key);
char 	decryption_64(u_klein_64 message , u_klein_64 cipher , u_klein_64 key);

char 	set_u_klein_64(u_klein_64 rop, char* str);


//   80 BITS   //////////////////////////////////////////////
typedef unsigned char 	u_klein_80[10];






//   96 BITS   //////////////////////////////////////////////
typedef unsigned char 	u_klein_96[12];




#endif





















