#ifndef 	__KLEIN_H__
#define 	__KLEIN_H__


#include 	<stdio.h>
#include 	<stdlib.h>
#include	<time.h>


#define		NIBBLES_NB	16
#define		ROUNDS_NB	12

unsigned char 	*Sbox;


typedef	unsigned char	Nibble;
typedef unsigned char	u_klein_64[16];		// each nibble is an unsigned char
typedef	u_klein_64		Key[ROUNDS_NB + 1];


// utils.c

void	u_klein_dcp(u_klein_64 a1, u_klein_64 a2);
char	hex2char(Nibble hex);

char 	set_u_klein_64(u_klein_64 rop , char* str);
void 	print_u_klein_64(u_klein_64 op);
char 	set_nibble_64(u_klein_64 op , char i , char nibble);
char 	get_nibble_64(u_klein_64 op , char i);


// encrypt.c

char 	encryption_64(u_klein_64 cipher , u_klein_64 message , u_klein_64 key);
char 	decryption_64(u_klein_64 message , u_klein_64 cipher , u_klein_64 key);


// key_schedule.c

void	key_schedule(Key key, u_klein_64 input_key);
void	generate_master_key(u_klein_64 master_key);
void	derive_new_subkey(u_klein_64 input, u_klein_64 output, int round);


// display.c

void	display_key(Key key);
void	display_u_klein(u_klein_64 uk);


#endif





















