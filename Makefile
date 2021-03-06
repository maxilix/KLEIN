NAME = klein

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = 	sources/display.c 				\
		sources/encrypt.c 				\
		sources/key_schedule.c 			\
		sources/reverse_key_schedule.c 	\
		sources/utils.c					\
		sources/seven_rounds_attack.c	\
		sources/eight_rounds_attack.c	\
		sources/prng.c					\
		sources/cheating.c 				\
		sources/tables.c


all :
	$(CC) $(CFLAGS) sources/main.c $(SRCS) -o $(NAME)

test :
	$(CC) sources/main_test.c $(SRCS) -o test

multithreading :
	$(CC) sources/main_multithreading.c $(SRCS) -lpthread -o multithreading

Wless :
	$(CC) sources/main.c $(SRCS) -o $(NAME)





