##
## Makefile for  in /home/truong_g/rendu/PSU_2015_strace
## 
## Made by Tony
## Login   <truong_g@epitech.net>
## 
## Started on  Mon Apr  4 21:22:32 2016 Tony
## Last update Sun May 15 23:23:01 2016 Tony
##

CC	=	gcc

NAME	=	server

SRCS	=	srcs/main.c		\
		srcs/server.c		\
		srcs/assign_client.c	\
		srcs/ftp_command.c	\
		srcs/ftp_command2.c	\
		srcs/ftp_command3.c	\
		srcs/ftp_tcommand.c	\
		srcs/command.c		\
		srcs/transfert.c	\

SRCS	+=	srcs/parser.c		\
		srcs/message.c		\
		srcs/utils.c		\
		srcs/error.c		\

OBJS	=	$(SRCS:.c=.o)

CFLAGS	+=	-W -Wall -Werror -Wextra
CFLAGS	+=	-I./include/

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
