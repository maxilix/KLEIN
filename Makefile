NAME = klein

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = 	sources/main.c 		\
		sources/klein.c 


all :
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

Wless :
	$(CC) $(SRCS) -o $(NAME)

fclean :
	rm -f $(NAME)

re : fclean all

