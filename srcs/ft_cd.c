/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 13:08:19 by cjamal            #+#    #+#             */
/*   Updated: 2019/12/02 17:32:15 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_cwd(char *ret, char *path)
{
	char	*tmp;
	char	*tmp2;
	int		diff;

	while (*path)
	{
		if ((tmp = ft_strchr(path, '/')) ||
				(tmp = ft_strchr(path, '\0')))
		{
			if ((diff = (tmp - path)) == 2 && ft_strnequ(path, "..", 2))
			{
				if (*ret && (tmp2 = ft_strrchr(ret, '/')))
					*tmp2 = 0;
			}
			else if (diff)
			{
				if ((tmp2 = ft_strrchr(ret, 0)) && (!*ret || tmp2[-1] != '/'))
					ft_strcat(tmp2, "/");
				ft_strncat(tmp2 + 1, path, diff);
			}
			path += diff + !!*tmp;
		}
	}
	!*ret ? ft_strcat(ret, "/") : 0;
}

void	ft_update_env(char *pwd, t_list **env, char *oldpwd)
{
	t_list **to_find;

	if ((to_find = ft_lstfind(env, "OLDPWD", 7)))
	{
		ft_lstmodifone((*to_find), ft_strjoin("OLDPWD=", oldpwd));
		ft_strreplace((*to_find)->content, '=', 0);
	}
	if ((to_find = ft_lstfind(env, "PWD", 4)))
	{
		ft_lstmodifone((*to_find), ft_strjoin("PWD=", pwd));
		ft_strreplace((*to_find)->content, '=', 0);
	}
	free(oldpwd);
	free(pwd);
}

char	*ft_cdnorm(char **cmd, char *cwd)
{
	if (*cmd[1] != '/')
		return (ft_strnjoin((char *[]){" ", cwd, "/", cmd[1]}, 4));
	else
		return (ft_strjoin(" ", cmd[1]));
}

char	*ft_cdexc(char **cmd, t_list **env, int *err, char *cwd)
{
	t_list **to_find;

	*err = 8;
	if (!cmd[1])
		if (!(to_find = ft_lstfind(env, "HOME", 5)))
			return (NULL);
		else
			return (ft_strjoin(" ", (*to_find)->content + 5));
	else if (ft_strequ(cmd[1], "-"))
	{
		if (!(to_find = ft_lstfind(env, "OLDPWD", 7)))
			return (NULL);
		else
			return (ft_strjoin(" ", (*to_find)->content + 7));
	}
	else if (!is_dir(cmd[1]))
	{
		*err = 6;
		return (NULL);
	}
	else
		return (ft_cdnorm(cmd, cwd));
}

void	ft_cd(char **cmd, t_list **env)
{
	char	*st;
	int		err;
	char	*pwd;

	if (cmd[1] && cmd[2])
		return (ft_print_error(cmd[0], ERR_MNARGS, 0));
	pwd = getcwd(NULL, 0);
	if (!(st = ft_cdexc(cmd, env, &err, pwd)))
	{
		free(pwd);
		return (ft_print_error(cmd[0], err, 0));
	}
	if (st && !access(st + 1, F_OK))
	{
		*st = 0;
		ft_get_cwd(st, st + 2);
		if (!chdir(st))
			return (ft_update_env(st, env, pwd));
		free(st);
		free(pwd);
		return (ft_print_error(cmd[0], ERR_PRMDND, 0));
	}
	free(pwd);
	free(st);
	return (ft_print_error(cmd[0], ERR_NTFOUND, 0));
}
