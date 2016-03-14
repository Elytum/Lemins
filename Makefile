# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achazal <achazal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 11:54:29 by achazal           #+#    #+#              #
#    Updated: 2014/12/13 12:55:35 by achazal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -------------Compilateur------------------#
CC		=	gcc
#--------------Name-------------------------#
NAME	=	lem_in
MYPATH	=	$(HOME)
#--------------Sources----------------------#
FILES	=	main.c		\
			solve.c		\
			tell.c		\
			parser.c	\
			vector.c	\
			vector2.c	\
			htable.c	\
			htable2.c

INC		=	-I./includes -I ./libft
LIBS	=	libft/libft.a
CCFLAGS	=	-Wall -Wextra -Werror -g -O3

SRCS	=	$(addprefix srcs/, $(FILES))
OBJS	=	$(SRCS:.c=.o)

#--------------Actions----------------------#

.PHONY: LIBRARIES $(NAME) clean fclean re

all: $(NAME)

LIBRARIES:
	@make -C libft

$(NAME): LIBRARIES $(OBJS)
	$(CC) $(CCFLAGS) $(INC) $(OBJS) -o $(NAME) $(LIBS) -O3

%.o: %.c
	$(CC) $(CCFLAGS) -c  $(INC) $< -o $@
	
clean:
	@make clean -C libft
	rm -f $(OBJS)
	
fclean:	clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean
	make fclean -C libft
	make
