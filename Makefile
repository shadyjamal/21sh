# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/29 15:53:22 by aait-ihi          #+#    #+#              #
#    Updated: 2020/01/17 16:28:17 by cjamal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

LIB_FT = libft/libft.a

FLAGS = -Wall -Werror -Wextra -g
SRC = cd.c echo.c env.c main.c parsing.c shellmain.c utilslst.c redirections_create.c\
		parse_cmd_tab.c redirections_store.c redirections_exec.c debug.c free.c exec.c utilsfd.c exec_pipe.c

CC = gcc

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIB_FT) : lib

lib:
	make -C libft

$(NAME): $(OBJ) $(LIB_FT)
	$(CC) $(FLAGS) $(OBJ) $(LIB_FT) -lreadline -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	/bin/rm -f $(OBJ)
	make clean -C libft

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C libft

re: fclean all
