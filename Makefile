# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/29 15:53:22 by aait-ihi          #+#    #+#              #
#    Updated: 2020/01/25 00:17:54 by cjamal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

LIB_FT = libft/libft.a

LIB_READLINE = readline/readline.a

FLAGS = -Wall -Werror -Wextra

SRC =	cd.c echo.c env.c exec.c exec_pipe.c free.c main.c parse_cmd_tab.c\
		redirections_create.c redirections_exec.c redirections_store.c shellmain.c\
		utilsfd.c utilslst.c parsing.c parse_arg.c parse_helper.c

CC = gcc

OBJ = $(SRC:.c=.o)

all: makelib $(NAME)

makelib :  
	@make -C readline
	@make -C libft

$(NAME): $(OBJ) $(LIB_FT) $(LIB_READLINE)
	$(CC) $(FLAGS) $(OBJ) -ltermcap $(LIB_FT) $(LIB_READLINE)  -o $(NAME)

%.o : %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	/bin/rm -f $(OBJ)
	make clean -C libft
	make clean -C readline

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C libft
	make fclean -C readline

re: fclean all
