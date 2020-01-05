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


// encrypt.c

void	add_round_key(u_klein rop , u_klein op , u_klein roundKey);
void 	sub_nibbles(u_klein rop , u_klein op);
void 	rotate_nibbles(u_klein rop , u_klein op);
void 	unrotate_nibbles(u_klein rop , u_klein op);
void 	mix_nibbles(u_klein rop , u_klein op);
void 	unmix_nibbles(u_klein rop , u_klein op);

unsigned char 	mul2(unsigned char op);
unsigned char 	mul3(unsigned char op);
unsigned char 	mul9(unsigned char op);
unsigned char 	mul11(unsigned char op);
unsigned char 	mul13(unsigned char op);
unsigned char 	mul14(unsigned char op);

void	encrypt(u_klein cipher , u_klein plain , Key key);
void	decrypt(u_klein deciphered , u_klein cipher , Key key);


// seven_rounds_attack.c

int		sevenRoundsAttack(u_klein master_key);
void	init_d(u_klein d);
int		findGoodCouples(const u_klein d, u_klein good_couples[8][2]);
void	halfkey(const unsigned long k);

#endif





















