#include "minishell.h"
#include <fcntl.h>

void save_stdin_stdout(int *std)
{

	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	std[2] = dup(STDERR_FILENO);
}

void restore_stdin_stdout(int *std)
{
	dup2(std[0], STDIN_FILENO);
	close(std[0]);
	dup2(std[1], STDOUT_FILENO);
	close(std[1]);
	dup2(std[2], STDERR_FILENO);
	close(std[2]);
}

void ft_execsimple_cmd(t_cmd_holder *hold, t_env_var *var, int *ret)
{
	char *cmdpath;

	cmdpath = NULL;
	save_stdin_stdout(hold->fd_backup);
	if (!ft_exec_redirections(*(hold->tab_redir)))
	{
		if (hold->tabpipe)
		{
			*ret = ft_exec_builtin(hold, var, 0);
			if (*ret == NO_BUILTIN)
				*ret = ft_exec_bin(hold->tabpipe[0], var, hold->env, 1);
		}
	}
	restore_stdin_stdout(hold->fd_backup);
}

void ft_execpipe(t_cmd_holder *hold, int pipecount, t_env_var *var, int *ret)
{
	int fd[2 * pipecount];
	int i;

	ft_pipefd(fd, pipecount); /* Initialize pipes */
	save_stdin_stdout(hold->fd_backup);
	i = 0;
	while (i < pipecount + 1)
	{
		if (fork_process() == 0)
		{
			if (i != 0)
				dup2(fd[2 * (i - 1)], 0);
			if (i != pipecount)
				dup2(fd[2 * i + 1], 1);
			ft_closefd(2 * pipecount, fd);	/* Close all fd */
			if (!(*ret = ft_exec_redirections(hold->tab_redir[i]))) /* Redirection */
			{
				if (hold->tabpipe)
				{
					*ret = ft_exec_builtin(hold, var, i);
					if (*ret == NO_BUILTIN)
						*ret = ft_exec_bin(hold->tabpipe[i], var, hold->env, 0);
				}
			}
			*ret ? exit(EXIT_FAILURE) : exit(EXIT_SUCCESS);
		}
		i++;
	}
	ft_closefd(2 * pipecount, fd);
	restore_stdin_stdout(hold->fd_backup);
	while (i--)
		wait(ret);
}
