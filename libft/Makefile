# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/12 13:56:01 by cjamal            #+#    #+#              #
#    Updated: 2019/11/12 13:56:11 by cjamal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = $(wildcard *.c)

FLAGS = -Wall -Wextra -Werror

CC = gcc $(FLAGS)

OBJ = $(patsubst %.c,%.o,$(SRC))

LIB = ar rc $(NAME) $(OBJ)

all : $(NAME)

%.o : %.c 
	@$(CC) -o $@ -c $<

$(NAME) : $(OBJ)
	@$(LIB)
	@ranlib $(NAME)

clean	: 
	@rm -f $(OBJ)

fclean	: clean
	@rm -f $(NAME)

re : fclean all
