#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/20 21:34:10 by smarie-c          #+#    #+#              #
#    Updated: 2014/03/17 12:05:03 by smarie-c         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = htable

SRC = htable.c

OBJ = $(SRC:.c=.o)

LIBNAME = htable.a

FLAGS = -Wall -Werror -Wextra

HEAD = ./

all: $(NAME)

$(NAME):
	@gcc -c $(SRC) -I $(HEAD) $(FLAGS)
	@ar rc $(LIBNAME) $(OBJ)
	@ranlib $(LIBNAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(LIBNAME)

re: fclean all
