/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 23:20:37 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/29 12:49:09 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_cwd(char *ret, char *path)
{
	char	*tmp;
	char	*tmp2;
	int		diff;

	*ret = 0;
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
			else if (diff && *path != '.')
			{
				if ((tmp2 = ft_strchr(ret, 0)) && (!*ret || tmp2[-1] != '/'))
					ft_strcat(tmp2, "/");
				ft_strncat(tmp2 + 1, path, diff);
			}
			path += diff + !!*tmp;
		}
	}
	!*ret ? ft_strcat(ret, "/") : 0;
}

void	ft_update_pwd(char *path, t_env_var *var)
{
	const char	*pwd = var->pwd->content;

	ft_lstmodifone(var->oldpwd, ft_strjoin("OLDPWD=", (pwd ? pwd + 4 : "")));
	ft_lstmodifone(var->pwd, ft_strjoin("PWD=", path));
	ft_strreplace(var->oldpwd->content, '=', 0);
	ft_strreplace(var->pwd->content, '=', 0);
}

int		change_dir(t_env_var *var, char *path, char *dir)
{
	dir = dir ? dir : var->home->content + 5;
	dir = ft_strequ(dir, "-") ? var->oldpwd->content + 7 : dir;
	if (path && !access(path + 1, F_OK))
	{
		if (ft_is_dir(path))
		{
			free(path);
			return (PRINT_ERROR(dir, NOT_DIR));
		}
		ft_get_cwd(path, path + 2);
		if (!chdir(path))
		{
			ft_update_pwd(path, var);
			free(path);
			return (0);
		}
		free(path);
		return (PRINT_ERROR(dir, PERM_DENYD));
	}
	free(path);
	return (PRINT_ERROR(dir, FILE_NOTFOUND));
}

int		ft_cd(char **cmd, t_env_var *v, char *pt)
{
	char		buf[4097];
	static char	s[] = " ";

	buf[4096] = 0;
	if (!cmd[1])
	{
		if (!v->home->content)
			return (PRINT_ERROR("HOME", NOT_SET));
		pt = ft_strjoin(" ", v->home->content + 5);
	}
	else if (ft_strequ(cmd[1], "-"))
	{
		if (!v->oldpwd->content)
			return (PRINT_ERROR("OLDPWD", NOT_SET));
		pt = ft_strjoin(" ", v->oldpwd->content + 7);
	}
	else if (*cmd[1] != '/')
	{
		if (v->pwd->content)
			pt = ft_strnjoin((char*[]){s, v->pwd->content + 4, "/", cmd[1]}, 4);
		else
			pt = ft_strnjoin((char*[]){" ", getcwd(buf, 4096), "/", cmd[1]}, 4);
	}
	return (change_dir(v, (pt ? pt : ft_strjoin(" ", cmd[1])), cmd[1]));
}
