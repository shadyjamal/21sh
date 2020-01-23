/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 23:23:56 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/20 12:42:13 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int		get_virtua_line_count(t_readline *readline)
{
	int			count;
	int			i;
	const int	*details = readline->line_props.details;

	i = 0;
	count = !!((details[i] + readline->o_cursor.x) % readline->col);
	count += ((details[i] + readline->o_cursor.x) / readline->col);
	i++;
	while (i < readline->line_props.linecount)
	{
		count += !!(details[i] % readline->col) + (details[i] / readline->col);
		i++;
	}
	return (count);
}

void	update_o_cursor(t_readline *env)
{
	int	diff;

	diff = (get_virtua_line_count(env) + env->o_cursor.y) - env->row;
	if (diff > 0)
	{
		env->o_cursor.y -= diff;
		set_virtual_origin(env);
	}
}

void	get_cursor_position(t_readline *readline)
{
	char	*buff;
	int		col;
	int		row;

	buff = (char[21]){0};
	while (1)
	{
		ft_putstr_fd("\e[6n", 0);
		col = read(0, buff, 20);
		buff[col] = 0;
		if (ft_strchr(buff, '['))
			break ;
	}
	buff = ft_skip_unitl_char(buff, "[", NULL);
	row = ft_atoi(buff + 1);
	buff = ft_skip_unitl_char(buff, ";", NULL);
	col = ft_atoi(buff + 1);
	readline->o_cursor = (t_point){col - 1, row - 1};
	readline->ov_cursor = readline->o_cursor;
}

char	*remove_unprintable_chars(char *str)
{
	char	*ret;
	int		i;

	ret = str;
	i = 0;
	if (str)
	{
		while (*str)
		{
			if (ft_isprint(*str) || *str == '\n')
			{
				ret[i++] = *str;
			}
			str++;
		}
		ret[i] = 0;
	}
	return (ret);
}

int		output(int c)
{
	ft_putchar(c);
	return (0);
}
