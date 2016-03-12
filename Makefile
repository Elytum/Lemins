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
			htable.c

INC		=	-I./includes -I ./libft/includes
LIBS	=	libft/libft.a
CCFLAGS	=	-Wall -Wextra -Werror -g

SRCS	=	$(addprefix srcs/, $(FILES))
OBJS	=	$(SRCS:.c=.o)

#--------------Actions----------------------#

.PHONY: LIBRARIES $(NAME) clean fclean re test

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
	rm -f $(NAME)

re: fclean
	make re -C libft
	make
