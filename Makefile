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


# Bonus 1 : DONE
#	export

# Bonus 2 : DONE
#	unset
#	bye

# Bonus 3
#	pwd

# Bonus 4
#	eval

# Bonus 5
#	

# -------------Compilateur------------------#
CC		=	gcc
#--------------Name-------------------------#
NAME	=	lem_in
MYPATH	=	$(HOME)
#--------------Sources----------------------#
FILES	=	main.c					\
			analyse.c				\
			errors.c				\
			extract.c

INC		=	-I ./includes -I ./libft -I ./htable
LIBS	=	libft/libft.a htable/htable.a
CCFLAGS	=	-Wall -Wextra -Werror -g

SRCS	=	$(addprefix srcs/, $(FILES))
OBJS	=	$(SRCS:.c=.o)

#--------------Actions----------------------#

.PHONY: LIBRARIES $(NAME) clean fclean re

all: $(NAME)

LIBRARIES:
	@make -C libft
	@make -C htable

$(NAME): LIBRARIES $(OBJS)
	$(CC) $(CCFLAGS) $(INC) $(OBJS) -o $(NAME) $(LIBS) -O3

%.o: %.c
	$(CC) $(CCFLAGS) -c  $(INC) $< -o $@
	
clean:
	@make clean -C libft
	@make clean -C htable
	rm -f $(OBJS)
	
fclean:	clean
	rm -f $(NAME)

re: fclean all
	make
