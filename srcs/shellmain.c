/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellmain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:54:20 by cjamal            #+#    #+#             */
/*   Updated: 2019/12/03 12:06:22 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmd_access(char *cmd)
{
	if (!access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (1);
		else
			return (2);
	}
	return (0);
}

char	*testpaths(char *cmd, char **paths, int *permdeny)
{
	int		i;
	int		ret;
	char	*path;

	i = 0;
	while (paths[i])
	{
		if (!(path = ft_strnjoin((char *[]){paths[i], "/", cmd}, 3)))
			return (NULL);
		if ((ret = cmd_access(path)) == 1)
			return (path);
		*permdeny = ret == 2 ? ret : 0;
		free(path);
		i++;
	}
	return (NULL);
}

char	*findpath(char *cmd, t_list **env)
{
	char	*path;
	int		permdeny;
	char	**paths;
	t_list	**getpath;

	paths = NULL;
	path = NULL;
	permdeny = 0;
	if (ft_strcmp(cmd, "..") &&
		ft_strcmp(cmd, ".") && (getpath = ft_lstfind(env, "PATH", 5)))
	{
		paths = ft_strsplit((*getpath)->content + 5, ':');
		path = testpaths(cmd, paths, &permdeny);
	}
	freetab(paths);
	!path ? ft_print_error(cmd, permdeny, 0) : 0;
	return (path);
}

void	execcmd(char **cmd, t_list *env, char *cmd_path)
{
	char	**tab_env;
	pid_t	parrent;
	int		status;

	tab_env = list_to_tab(env, 1);
	parrent = fork();
	g_childprc_pid = parrent;
	if (parrent < 0)
	{
		freetab(tab_env);
		return ;
	}
	if (parrent > 0)
	{
		wait(&status);
		if (WIFSIGNALED(status))
			ft_putstr("\n");
	}
	if (parrent == 0)
		execve(cmd_path, cmd, tab_env);
	freetab(tab_env);
}

void	ft_shellmain(char **cmd, t_list *env)
{
	char	*cmd_path;
	int		ret;

	cmd_path = NULL;
	if (ft_strchr(cmd[0], '/') && !is_dir(cmd[0]))
	{
		ret = cmd_access(cmd[0]);
		ret == 1 ? cmd_path = cmd[0] : 0;
		if (ret != 1)
			return (ft_print_error(cmd[0], ret, 0));
	}
	else if (cmd[0] && cmd[0][0])
		cmd_path = findpath(cmd[0], &env);
	if (cmd_path)
	{
		execcmd(cmd, env, cmd_path);
		if (cmd_path != cmd[0])
			free(cmd_path);
	}
}
