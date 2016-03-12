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

NAME = libft

SRC = ft_isalnum.c ft_memcmp.c ft_strcpy.c ft_strnstr.c ft_isalpha.c \
	ft_memcpy.c ft_strdup.c ft_strrchr.c ft_isascii.c ft_memmove.c \
	ft_strlcat.c ft_atoi.c ft_memccpy.c ft_strchr.c ft_strstr.c \
	ft_strncmp.c ft_bzero.c ft_memchr.c ft_strcmp.c ft_strncpy.c \
	ft_isdigit.c ft_memset.c ft_strlen.c ft_tolower.c ft_isprint.c \
	ft_strcat.c ft_strncat.c ft_toupper.c \
	ft_strsub.c ft_strnew.c ft_putchar.c ft_putstr.c \
	ft_strequ.c ft_strmapi.c ft_strmap.c ft_strjoin.c ft_striteri.c \
	ft_striter.c ft_strnequ.c ft_strdel.c ft_strclr.c ft_putstr_fd.c \
	ft_putnbr_fd.c ft_putnbr.c ft_putendl_fd.c ft_putendl.c \
	ft_putchar_fd.c ft_memdel.c ft_memalloc.c ft_strtrim.c ft_strsplit.c \
	ft_itoa.c ft_abs_val.c ft_fibonacci.c ft_isspace.c ft_memdup.c \
	ft_tablen.c ft_strsplit_trim.c ft_delsplit.c get_next_line.c ft_oddprev.c

OBJ = $(SRC:.c=.o)

LIBNAME = libft.a

FLAGS = -Wall -Werror -Wextra

HEAD = ./includes

all: $(NAME)

$(NAME):
	@gcc -c $(SRC) -I $(HEAD) $(FLAGS)
	@ar rc $(LIBNAME) $(OBJ)
	@ranlib $(LIBNAME)

testmain:
	@rm -f a.out
test:
	@cc $(SRC) ft_ls.c
clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(LIBNAME)

re: fclean all
