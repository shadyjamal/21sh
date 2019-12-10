/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 06:55:35 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/03 12:05:23 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		escap(char *str, const char *from, char *to, int size)
{
	ft_translate(str - size, from, to);
	return (1);
}

char	*ft_parse_arg(char *buffer, char *buff, const char *cmp)
{
	char *tmp;

	tmp = buffer;
	while (*buffer && !ft_isinstr(*buffer, cmp))
		*buff++ = *buffer++;
	*buff = 0;
	if (*buffer == '"' && !ft_strequ(cmp, "\""))
		return (ft_parse_arg(buffer + 1, buff, "\""));
	if (*buffer == '"' && ft_strequ(cmp, "\"") &&
			escap(buff, "~", "\2", buffer - tmp))
		return (ft_parse_arg(buffer + 1, buff, " \t'\""));
	if (*buffer == '\'' && !ft_strequ(cmp, "'"))
		return (ft_parse_arg(buffer + 1, buff, "'"));
	if (*buffer == '\'' && ft_strequ(cmp, "'") &&
			escap(buff, "$~", "\1\2", buffer - tmp))
		return (ft_parse_arg(buffer + 1, buff, " \t'\""));
	if (*cmp == '\'' || *cmp == '"')
	{
		ft_print_error(0, ERR_UNMATCHED, *cmp);
		return (NULL);
	}
	return (buffer);
}

char	*ft_parse_dollar(char *arg, t_list **env)
{
	char	*dolr;
	char	*tmp;
	char	*to_free;
	t_list	**var_env;
	int		len_var;

	dolr = arg;
	while (arg && (dolr = ft_strchr(dolr, '$')) && dolr[1])
	{
		*dolr++ = 0;
		len_var = ft_skip_unitl_char(dolr, SYMBOL) - dolr;
		tmp = "";
		if (*dolr == '$' && (dolr++ || 1))
			tmp = PID;
		else if ((var_env = ft_lstfind(env, dolr, len_var)))
			tmp = (*var_env)->content + len_var + 1;
		to_free = arg;
		arg = ft_strnjoin((char *[]){arg, tmp, dolr + len_var}, 3);
		dolr = arg + ft_strlen(to_free) + ft_strlen(tmp);
		free(to_free);
	}
	return (arg);
}

char	*ft_parse_tilde(char *tilde, t_list **env)
{
	char	*ret;
	t_list	**var_env;

	if (tilde && tilde[0] == '~')
	{
		if (tilde[1] == '/' || tilde[1] == '\0')
		{
			if (!(var_env = ft_lstfind(env, "HOME", 5)))
				ret = ft_strjoin("", &tilde[1]);
			else
				ret = ft_strjoin((*var_env)->content + 5, &tilde[1]);
			free(tilde);
			return (ret);
		}
		else if ((ret = ft_strjoin("/Users/", &tilde[1])))
		{
			if (!access(ret, F_OK))
			{
				free(tilde);
				return (ret);
			}
			free(ret);
		}
	}
	return (tilde);
}

t_list	*ft_parsecmd(char *buffer, t_list **env)
{
	char	*buff;
	char	*tmp;
	t_list	*args;

	if (!(buff = malloc(ft_strlen(buffer) + 1)))
		return (NULL);
	args = NULL;
	buffer = ft_skip_chars(buffer, "\t ");
	while (*buffer)
	{
		if (!(buffer = ft_parse_arg(buffer, buff, " \t'\"")))
		{
			ft_lstdel(&args, freecontent);
			free(buff);
			return (NULL);
		}
		buffer = ft_skip_chars(buffer, "\t ");
		tmp = ft_parse_dollar(ft_strdup(buff), env);
		tmp = ft_parse_tilde(tmp, env);
		ft_translate(tmp, "\1\2", "$~");
		ft_lstpushback(&args, tmp, ft_strlen(tmp) + !!tmp);
		free(tmp);
	}
	free(buff);
	return (args);
}
