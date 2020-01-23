/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 06:55:35 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/22 17:48:29 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_parse_dollar(char *arg, t_list **env)
{
	char *dolr;
	char *tmp;
	char *to_free;
	t_list **var_env;
	int len_var;

	dolr = arg;
	while (arg && (dolr = ft_strchr(dolr, '$')) && dolr[1])
	{
		*dolr++ = 0;
		len_var = ft_skip_unitl_char(dolr, NULL, ft_isnalnum) - dolr;
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

char *ft_parse_tilde(char *tilde, t_env_var *var)
{
	char *ret;

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

char *expand_tilde_$( char *buff, t_list **env, t_env_var *var)
{
	char *tmp;

	tmp = ft_parse_dollar(ft_strdup(buff), env);
	tmp = ft_parse_tilde(tmp, var);
	ft_translate(tmp, "\1\2", "$~");
	return (tmp);
}

t_list *parse_exit(char *buff, t_list *args)
{
	free(buff);
	ft_lstdel(&args);
	return (NULL);
}

t_list *ft_parsecmd(t_cmd_holder *hold, t_list **env, t_env_var *var)
{
	char *buff;
	char *tmp;
	t_list *args;

	if (!(buff = malloc(ft_strlen(hold->buff) + 1)))
		return (NULL);
	args = NULL;
	tmp = NULL;
	hold->cmd = ft_skip_chars(hold->buff, "\n\t ", NULL);
	while (*hold->cmd)
	{
		if (!(hold->cmd = ft_parse_arg(hold, &buff)))
			return (parse_exit(buff, args));
		hold->cmd = ft_skip_chars(hold->cmd, "\n\t ", NULL);
		tmp = expand_tilde_$(buff, env,var);
		ft_lstpushback(&args, tmp, ft_strlen(tmp) + !!tmp);
		free(tmp);
	}
	printlst(args);
	add_to_history(hold->buff, ft_strlen(hold->buff));
	free(buff);
	return (args);
}
