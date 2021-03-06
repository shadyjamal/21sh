/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 00:59:52 by cjamal            #+#    #+#             */
/*   Updated: 2020/01/24 01:55:19 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_translate_cmd(char **cmd)
{
	int i;

	i = -1;
	while (cmd[++i])
		ft_translate(cmd[i], "\1\2\5\6\7\x08\x09", "$~&;<>|");
}

int		exec_builtin_bin(t_cmd_holder *hold, t_env_var *var, _Bool fork, int i)
{
	int ret;

	ret = 0;
	if (hold->tabpipe)
	{
		if (hold->tabpipe[i])
		{
			ft_translate_cmd(hold->tabpipe[i]);
			ret = ft_exec_builtin(hold, var, i);
			if (ret == NO_BUILTIN)
				ret = ft_exec_bin(hold->tabpipe[i], var, hold->env, fork);
		}
	}
	return (ret);
}

void	ft_execsimple_cmd(t_cmd_holder *hold, t_env_var *var, int *ret)
{
	char *cmdpath;

	cmdpath = NULL;
	save_stdin_stdout(hold->fd_backup);
	if (!(*ret = ft_exec_redirections(*(hold->tab_redir))))
		(*ret = exec_builtin_bin(hold, var, 1, 0));
	restore_stdin_stdout(hold->fd_backup);
}

void	ft_execpipe(t_cmd_holder *hold, int pipecount, t_env_var *var, int *ret)
{
	int fd[2 * pipecount];
	int i;

	ft_pipefd(fd, pipecount);
	save_stdin_stdout(hold->fd_backup);
	i = -1;
	while (++i < pipecount + 1)
	{
		if (fork_process() == 0)
		{
			i ? dup2(fd[2 * (i - 1)], 0) : 0;
			(i != pipecount) ? dup2(fd[2 * i + 1], 1) : 0;
			ft_closefd(2 * pipecount, fd);
			if (!(*ret = ft_exec_redirections(hold->tab_redir[i])))
				(*ret = exec_builtin_bin(hold, var, 0, i));
			*ret ? exit(EXIT_FAILURE) : exit(EXIT_SUCCESS);
		}
	}
	ft_closefd(2 * pipecount, fd);
	restore_stdin_stdout(hold->fd_backup);
	while (i--)
		wait(ret);
}
