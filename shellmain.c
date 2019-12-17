/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellmain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:14:36 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/17 17:58:38 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmd_access(char *cmd)
{
	if (cmd && !ft_is_dir(cmd) && !access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (0);
		else
			return (2);
	}
	return (1);
}

char	*find(char *cmd, t_env_var *var)
{
	char	*path;
	int		ret;
	int		permdeny;
	char	**paths;
	int		i;

	permdeny = 0;
	i = 0;
	paths = ft_strsplit(var->path->content ? var->path->content + 5 : "", ":");
	while (paths && paths[i])
	{
		path = ft_strnjoin((char *[]){paths[i], "/", cmd}, 3);
		if (!(ret = cmd_access(path)))
		{
			ft_free_2d_tab(paths);
			return (path);
		}
		i++;
		ret == 2 ? permdeny = ret : 0;
		free(path);
	}
	ft_free_2d_tab(paths);
	PRINT_ERROR(cmd, permdeny ? PERM_DENYD : CMD_NOT_FOUND);
	return (NULL);
}

char		*ft_shellmain(char **cmd, t_env_var *var)
{
	char	*cmd_path;
	int		ret;

	if (ft_strchr(cmd[0], '/'))
	{
		if ((ret = cmd_access(cmd[0])))
		{
			PRINT_ERROR(cmd[0], CMD_NOT_FOUND);
			return (NULL);
		}
		cmd_path = ft_strdup(cmd[0]);
	}
	else
		cmd_path = find(cmd[0], var);
	return (cmd_path);
}
