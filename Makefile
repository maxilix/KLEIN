NAME = klein

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = 	sources/main.c 					\
		sources/display.c 				\
		sources/encrypt.c 				\
		sources/key_schedule.c 			\
		sources/reverse_key_schedule.c 	\
		sources/utils.c					\
		sources/seven_rounds_attack.c


all :
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

Wless :
	$(CC) $(SRCS) -o $(NAME)

fclean :
	rm -f $(NAME)

re : fclean all

