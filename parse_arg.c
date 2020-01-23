/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 23:57:05 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/22 18:03:05 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void merge_cmd(t_cmd_holder *hold, char *str)
{
	char *tmp;
	int len;

	tmp = hold->buff;
	len = ft_strlen(hold->buff);
	if ((hold->buff = ft_strnjoin((char *[]){hold->buff, "\n", str}, 3)))
		hold->cmd = hold->buff + len + 1;
	if (str)
		free(str);
	if (!hold->buff)
		hold->cmd = NULL;
	free(tmp);
}

char *sequel(char **buff, int *buff_len)
{
	char *line;

	if ((line = ft_readline(">")))
	{
		if (!(*buff = ft_realloc(*buff, *buff_len + 1, ft_strlen(line) + 1)))
		{
			free(line);
			return (NULL);
		}
		ft_strcat(*buff, "\n");
		(*buff_len)++;
	}
	return (line);
}

char *copy_to_buff(char *arg, char *buff, int *i, const char *cmp)
{
	while (arg && *arg && !ft_isinstr(*arg, cmp))
	{
		if (*arg == '\\')
			if (arg++ && !*arg)
				break;
		buff[(*i)++] = *arg++;
	}
	buff[*i] = 0;
	return (arg);
}

char *parse_redirections(t_cmd_holder *hold, char **buff, int *i)
{
	const int j = *i;
	const char c = *hold->cmd;

	while (*hold->cmd == c)
		buff[0][(*i)++] = *hold->cmd++;
	if (*i - j > 2)
	{
		ft_printf("parse error near `%c'\n", c);
		return (NULL);
	}
	(*i - j == 1 && *hold->cmd == '&') ? buff[0][(*i)++] = *hold->cmd++ : 0;
	buff[0][*i] = 0;
	hold->cmd = ft_skip_chars(hold->cmd, " \t\n", NULL);
	if (!*hold->cmd || ft_isinstr(*hold->cmd, SEPARATOR))
	{
		ft_printf("parse error near `%2s'\n", *hold->cmd ? hold->cmd : "\n");
		return (NULL);
	}
	return (hold->cmd);
}

char *parse_pipe(t_cmd_holder *hold, char **buff, int *i)
{
	const int j = *i;
	const char c = *hold->cmd;

	while (*hold->cmd == c)
		buff[0][(*i)++] = *hold->cmd++;
	buff[0][*i] = 0;
	if (*i - j > 2)
	{
		ft_printf("parse error near `%c'\n", c);
		return (NULL);
	}
	while (hold->cmd && !*(hold->cmd = ft_skip_chars(hold->cmd, " \t\n", NULL)))
		merge_cmd(hold, sequel(buff, i));
	if (hold->cmd && ft_isinstr(*hold->cmd, SEPARATOR))
	{
		ft_printf("parse error near `%c'\n", *hold->cmd);
		return(NULL);
	}
	return (hold->cmd);
}

char *parse_quotes(t_cmd_holder *hold, char **buff, int *i)
{
	char c = *hold->cmd++;;
	const int j = *i;

	while (1)
	{
		hold->cmd = copy_to_buff(hold->cmd, *buff, i, (char[2]){c, 0});
		if (!hold->cmd || *hold->cmd == c)
			break;
		merge_cmd(hold, sequel(buff, i));
	}
	if (c == '\'')
		ft_translate(*buff + j, "$~&;<>|", "\1\2\5\6\7\x08\x09");
	else
		ft_translate(*buff + j, "~&;<>|", "\2\5\6\7\x08\x09");
	return (hold->cmd + !!hold->cmd);
}

char *ft_parse_arg(t_cmd_holder *hold, char **buff)
{
	int index;

	index = 0;
	while (hold->cmd && *hold->cmd)
	{
		hold->cmd = copy_to_buff(hold->cmd, *buff, &index, ";|&><' \t\"\n");
		if (*hold->cmd == '"' || *hold->cmd == '\'')
			hold->cmd = parse_quotes(hold, buff, &index);
		else if ((*hold->cmd == '|' || *hold->cmd == '&') && index == 0)
			return (parse_pipe(hold, buff, &index));
		else if (*hold->cmd == ';' && index == 0)
		{
			while (*hold->cmd == ';')
				buff[0][index++] = *hold->cmd++;
			buff[0][index] = 0;
			return (hold->cmd);
		}
		else if (ft_isinstr(*hold->cmd, "<>") &&
					(index == 0 || (index == 1 && ft_isdigit(hold->cmd[-1]))))
			return (parse_redirections(hold, buff, &index));
		else
			break;
	}
	return (hold->cmd);
}
