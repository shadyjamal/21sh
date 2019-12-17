/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 06:55:35 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/29 13:52:35 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		escap(char *str, const char *from, char *to, int size)
{
	ft_translate(str - size, from, to);
	return (1);
}

char	*ft_parse_arg(char *arg, char *buff, const char *cmp)
{
	const char	*tmp = arg;

	while (*arg && !ft_isinstr(*arg, cmp))
	{
		if (*arg == '\\')
			if (arg++ && !*arg)
				break ;
		*buff++ = *arg++;
	}
	*buff = 0;
	if (*arg == '"' && *cmp != '"')
		return (ft_parse_arg(arg + 1, buff, "\""));
	if (*arg == '"' && *cmp == '"' && escap(buff, "~", "\2", arg - tmp))
		return (ft_parse_arg(arg + 1, buff, " \t'\""));
	if (*arg == '\'' && *cmp != '\'')
		return (ft_parse_arg(arg + 1, buff, "'"));
	if (*arg == '\'' && *cmp == '\'' && escap(buff, "$~", "\1\2", arg - tmp))
		return (ft_parse_arg(arg + 1, buff, " \t'\""));
	if (*cmp == '\'' || *cmp == '"')
	{
		PRINT_ERROR(UNMATCHED, cmp);
		return (NULL);
	}
	return (arg);
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

char	*ft_parse_tilde(char *tilde, t_env_var *var)
{
	char	*ret;

	if (tilde && tilde[0] == '~')
	{
		if (tilde[1] == '/' || tilde[1] == '\0')
		{
			ret = ft_strjoin(var->home->content + 5, &tilde[1]);
			free(tilde);
			return (ret);
		}
		if ((ret = ft_strjoin("/Users/", &tilde[1])) && !access(ret, F_OK))
		{
			free(tilde);
			return (ret);
		}
		free(ret);
	}
	return (tilde);
}

t_list	*ft_parsecmd(char *buffer, t_list **env, t_env_var *var)
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
			free(buff);
			ft_lstdel(&args);
			return (NULL);
		}
		buffer = ft_skip_chars(buffer, "\t ");
		tmp = ft_parse_dollar(ft_strdup(buff), env);
		tmp = ft_parse_tilde(tmp, var);
		ft_translate(tmp, "\1\2", "$~");
		ft_lstpushback(&args, tmp, ft_strlen(tmp) + !!tmp);
		free(tmp);
	}
	free(buff);
	return (args);
}
