# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/19 22:21:22 by aait-ihi          #+#    #+#              #
#    Updated: 2019/11/29 16:16:04 by aait-ihi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror
CC = gcc

OPTION = -c

INCLUDE = includes

LIBFT_HEADER = includes/libft.h

STRING_SRC = 	ft_atoi.c\
				ft_atoi_base.c\
				ft_isinstr.c\
				ft_putchar.c\
				ft_putchar_fd.c\
				ft_putendl.c\
				ft_putendl_fd.c\
				ft_putnbr.c\
				ft_putnbr_fd.c\
				ft_putstr.c\
				ft_putstr_fd.c\
				ft_realloc.c\
				ft_skipchr.c\
				ft_skipnchr.c\
				ft_strcat.c\
				ft_strchr.c\
				ft_strclr.c\
				ft_strcmp.c\
				ft_strcpy.c\
				ft_strdel.c\
				ft_strdup.c\
				ft_strequ.c\
				ft_strindexof.c\
				ft_striter.c\
				ft_striteri.c\
				ft_strjoin.c\
				ft_strlcat.c\
				ft_strlen.c\
				ft_strmap.c\
				ft_strmapi.c\
				ft_strncat.c\
				ft_strncmp.c\
				ft_strncpy.c\
				ft_strnequ.c\
				ft_strnew.c\
				ft_strnstr.c\
				ft_strrchr.c\
				ft_strsplit.c\
				ft_strstr.c\
				ft_strsub.c\
				ft_strtrim.c\
				ft_strtoupper.c\
				ft_wordcount.c\
				ft_strreplace.c\
				ft_skip_chars.c\
				ft_skip_until_char.c\
				ft_str_occurence.c\
				ft_strnjoin.c\
				ft_translate.c\
				ft_str_in_arr.c\
				ft_str_match.c\
				ft_free_2d_tab.c


BIGINT_SRC = 	aritmitic_op.c\
				conditional_op.c\
				ft_bipow.c\
				ft_ldtoa.c\
				special_case.c\

BITS_SRC =		ft_printbit.c \
				ft_reverse_bits.c

CHAR_SRC =		ft_isalnum.c\
				ft_isalpha.c\
				ft_isascii.c\
				ft_isprint.c\
				ft_iswhitespace.c\
				ft_tolower.c\
				ft_toupper.c

LIST_SRC =		ft_lstadd.c\
				ft_lstdel.c\
				ft_lstdelone.c\
				ft_lstiter.c\
				ft_lstmap.c\
				ft_lstnew.c\
				ft_lstpushback.c\
				ft_lstfind.c\
				ft_lstdup.c\
				ft_lstsize.c

MEMORY_SRC =	ft_bzero.c\
				ft_memalloc.c\
				ft_memccpy.c\
				ft_memchr.c\
				ft_memcmp.c\
				ft_memcpy.c\
				ft_memdel.c\
				ft_memmove.c\
				ft_memset.c

NUMBER_SRC =	buble_sort.c\
				ft_find_int.c\
				ft_declen.c\
				ft_isdigit.c\
				ft_isnbr.c\
				ft_itoa.c\
				ft_itoa_base.c\
				ft_max.c\
				ft_pow.c\
				ft_sqrt.c\
				ft_swap.c\
				ft_uitoa.c\
				ft_uitoa_base.c\
				int_rrot.c\
				int_rot.c\
				is_sorted_asc.c\
				is_sorted_desc.c\
				ft_int_max.c\
				ft_int_min.c

PRINTF_SRC = 	dispatcher.c\
				ft_printf.c\
				get_flags.c\
				get_options.c\
				set_color.c\
				set_flags.c\
				set_options.c\
				va_arg.c

SRC	=			get_next_line.c\
				ft_die.c\
				flags.c\
				ft_is_dir.c

OBJ =	$(BIGINT_SRC:%.c=%.o) $(STRING_SRC:%.c=%.o) $(BITS_SRC:%.c=%.o) $(CHAR_SRC:%.c=%.o) $(LIST_SRC:%.c=%.o) $(MEMORY_SRC:%.c=%.o) $(NUMBER_SRC:%.c=%.o) $(PRINTF_SRC:%.c=%.o) $(SRC:%.c=%.o)


all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(FLAG) $(OPTION) -I $(INCLUDE) $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

 %.o : bigint/%.c includes/bigint.h includes/libft.h
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $@ -c $<

 %.o : bits/%.c $(LIBFT_HEADER)
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $@ -c $<

 %.o : char/%.c $(LIBFT_HEADER)
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $@ -c $<

 %.o : ft_printf/%.c includes/printf.h $(LIBFT_HEADER)
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $@ -c $<

%.o : list/%.c $(LIBFT_HEADER)
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $@ -c $<

 %.o : memory/%.c $(LIBFT_HEADER)
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $@ -c $<

 %.o : number/%.c $(LIBFT_HEADER)
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $@ -c $<

 %.o : string/%.c $(LIBFT_HEADER)
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $@ -c $<

 %.o : %.c $(LIBFT_HEADER)
	$(CC) $(CFLAGS) -I $(INCLUDE) -o $@ -c $<

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

