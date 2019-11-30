#ifndef 	__KLEIN_H__
#define 	__KLEIN_H__


#include 	<stdio.h>
#include 	<stdlib.h>
#include	<time.h>


#define		NIBBLES_NB	16
#define		ROUNDS_NB	12
#define		SEED		15

extern const unsigned char 	Sbox[16];


typedef char			Bool;
typedef	unsigned char	Nibble;				// each nibble is an unsigned char
typedef Nibble			u_klein[16];
typedef	u_klein			Key[ROUNDS_NB + 1];


// utils.c

void	u_klein_dcp(u_klein rop, u_klein const op);
char	hex2char(Nibble const hex);
Nibble	char2nibble(char const c);
Bool	str2u_klein(u_klein rop, char const *str);
int		u_klein_cmp(u_klein const op1, u_klein const op2);


// encrypt.c

char 	encryption_64(u_klein cipher , u_klein message , u_klein key);
char 	decryption_64(u_klein message , u_klein cipher , u_klein key);


// key_schedule.c

void	key_schedule(Key key, char const *input_key);
void	random_master_key(u_klein master_key);
void	derive_new_subkey(u_klein const input, u_klein output, int round);


// reverse_key_schedule.c

Bool	reverse_key_schedule(u_klein master_key, u_klein const round_key, int round);
Bool	reverse_round(u_klein const input, u_klein output, int round);


// display.c

void	display_key(Key const key);
void	display_u_klein(u_klein const uk);


#endif





















