#ifndef 	__KLEIN_H__
#define 	__KLEIN_H__


#include 	<stdio.h>
#include 	<stdlib.h>
#include	<time.h>


#define		NIBBLES_NB				16
#define		NIBBLES_NB_DIV2			8
#define		NIBBLES_NB_DIV4			4
#define		ROUNDS_NB				7
#define		MAX_LONG				4294967296
#define		MAX_LONG_DIV2			2147483648
#define 	MAX_LONG_LONG 			18446744073709551616
#define		UKLEIN_STRING_LENGTH	18
#define		MASTER_KEY				"0x0123456789ABCDEF"
#define		GOOD_COUPLES_NB			8  
#define		ERROR_THRESHOLD			2

#define 	KNUTH_LEWIS_GENERATOR_A 	1664525
#define 	KNUTH_LEWIS_GENERATOR_C 	1013904223
#define 	KNUTH_LEWIS_GENERATOR_M 	4294967296
#define 	HAYNES_GENERATOR_A 			6364136223846793005
#define 	HAYNES_GENERATOR_M 			18446744073709551616


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
void	u_klein_xor(u_klein rop, u_klein const op1, u_klein const op2);
void	init_d(u_klein d);


// key_schedule.c

void	key_schedule(Key key, u_klein const input_master_key);
void	init_keys(Key keys);
void	random_master_key(u_klein master_key);
void	derive_new_subkey(u_klein const input, u_klein output, int round);


// reverse_key_schedule.c

Bool	reverse_key_schedule(u_klein master_key, u_klein const round_key, int round);
void	full_reverse_key_schedule(Key keys, u_klein const last_round_key);
void	reverse_round(u_klein output, u_klein const input, int round);


// display.c

void	display_key(Key const key);
void	display_u_klein(u_klein const uk);
void	print_u_klein(u_klein const u, char *str);
void	display_xor(u_klein const u1, u_klein const u2, char const *str);
void	display_cipher_differential(u_klein m);


// encrypt.c

void	add_round_key(u_klein rop , u_klein const op , u_klein const roundKey);
void 	sub_nibbles(u_klein rop , u_klein const op);
void 	rotate_nibbles(u_klein rop , u_klein const op);
void 	unrotate_nibbles(u_klein rop , u_klein const op);
void 	mix_nibbles(u_klein rop , u_klein const op);
void 	unmix_nibbles(u_klein rop , u_klein const op);

unsigned char 	mul2(unsigned char const op);
unsigned char 	mul3(unsigned char const op);
unsigned char 	mul9(unsigned char const op);
unsigned char 	mul11(unsigned char const op);
unsigned char 	mul13(unsigned char const op);
unsigned char 	mul14(unsigned char const op);

void	encrypt_round(u_klein cipher, u_klein const roundKey);
void	encrypt(u_klein cipher , u_klein const plain , Key const key);
void	decrypt(u_klein deciphered , u_klein const cipher , Key const key);
void	oracle(u_klein cipher, u_klein const plain);


// seven_rounds_attack.c

Bool		seven_rounds_attack(u_klein masterKey);
Bool		verify_good_couple_condition(u_klein m1, u_klein m2);
Bool		add_good_couple(u_klein goodCouples[GOOD_COUPLES_NB][4], u_klein m1, u_klein m2, int cnt);
void		init_d(u_klein d);
void		halfkey(u_klein kTilde, long long k);
Bool 		verify_kTilde(u_klein const kTilde, u_klein const goodCouples[4]);
Bool 		find_full_key(u_klein rop, u_klein const kTilde, u_klein const goodCouples[GOOD_COUPLES_NB][4]);
void 		fill_test_key(u_klein testKey, long long k);


// eight_rounds_attack.c

Bool		eight_rounds_attack(u_klein masterKey);
Bool		verify_good_couple(u_klein goodCouples[GOOD_COUPLES_NB][4]);
void		neutral_byte_modification(u_klein rop, long long k);


// prng_knuth_lewis.c

void 	init_generators();
void 	random_u_klein_knuthlewis(u_klein rop);
void 	random_u_klein_haynes(u_klein rop);


// cheating.c

Bool	verify_good_couple_condition_cheating(u_klein const m1, u_klein const m2);

#endif





















