NAME = klein

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = 	sources/display.c 				\
		sources/encrypt.c 				\
		sources/key_schedule.c 			\
		sources/reverse_key_schedule.c 	\
		sources/utils.c					\
		sources/seven_rounds_attack.c	\
		sources/eight_rounds_attack.c	


all :
	$(CC) $(CFLAGS) sources/main.c $(SRCS) -o $(NAME)

test :
	$(CC) $(CFLAGS) sources/testmain.c $(SRCS) -o $(NAME)

Wless :
	$(CC) $(SRCS) -o $(NAME)

fclean :
	rm -f $(NAME)

re : fclean all


