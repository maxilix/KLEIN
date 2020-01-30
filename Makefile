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
	$(CC) sources/testmain.c $(SRCS) -o $(NAME)

couples_search :
	$(CC) sources/main_couples_search.c $(SRCS) -lpthread -o couples_search

Wless :
	$(CC) sources/main.c $(SRCS) -o $(NAME)

fclean :
	rm -f $(NAME)

re : fclean all




