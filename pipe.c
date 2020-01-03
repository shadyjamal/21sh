#include "minishell.h"
#include <fcntl.h>

pid_t fork_process(void)
{
	pid_t fork_ret;

	fork_ret = fork();
	if (fork_ret < 0)
	{
		ft_putendl_fd("failed to fork", 2);
		exit(EXIT_FAILURE);
	}
	return (fork_ret);
}

void ft_closefd(int fdcount, int *fd)
{
	int i;

	i = 0;
	while (i < fdcount)
	{
		close(fd[i]);
		i++;
	}
}

void ft_pipefd(int *fd, int pipecount)
{
	int i;

	i = 0;
	while (i < pipecount)
	{
		pipe(&fd[2 * i]);
		i++;
	}
}

void	save_stdin_stdout(int *std)
{

	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
}

void				restore_stdin_stdout(int *std)
{
	dup2(std[0], STDIN_FILENO);
	close(std[0]);
	dup2(std[1], STDOUT_FILENO);
	close(std[1]);
}

void ft_execsimple_cmd(t_cmd_holder *hold,t_env_var *var)
{
	int			ret;
	char		*cmdpath;
	char		**tabenv;	
	int			backup[2];

	cmdpath = NULL;
	if (hold->tabpipe[0] != NULL)
	{
		save_stdin_stdout(backup);
		tabenv = list_to_tab(hold->env, 1);
		ft_exec_redirections(*(hold->tab_redir));
		ret = dispatch(hold->tabpipe[0], &hold->env, var, &cmdpath);
		if (cmdpath)
		{
			if (fork_process() == 0)
			{
				if (execve(cmdpath, hold->tabpipe[0], tabenv) == -1)
					exit(EXIT_FAILURE);
			}
			else
				wait(NULL);
		}
		else if (ret)
		{
			write(2, "error\n", 6);
		}
		restore_stdin_stdout(backup);
	}
}

void ft_execpipe(t_cmd_holder *hold, int pipecount,t_env_var *var)
{
	int fd[2 * pipecount];
	int i;
	char *cmdpath;
	int ret;
	char **tabenv;
	int	backup[2];

	tabenv = list_to_tab(hold->env, 1);
	ft_pipefd(fd, pipecount); /* Initialize pipes */
	i = 0;
	while (hold->tabpipe[i] != NULL)
	{
		if (fork_process() == 0)
		{
			cmdpath = NULL;
			if (i != 0)
				dup2(fd[2 * (i - 1)], 0);
			if (hold->tabpipe[i + 1] != NULL)
				dup2(fd[2 * i + 1], 1);
			ft_closefd(2 * pipecount, fd); /* Close all fd */
			save_stdin_stdout(backup);
			// Redirection
			ft_exec_redirections(hold->tab_redir[i]);
			// Exec
			ret = dispatch(hold->tabpipe[i], &hold->env, var, &cmdpath);
			if (cmdpath)
			{
				if (execve(cmdpath, hold->tabpipe[i], tabenv) == -1)
					exit(EXIT_FAILURE);
			}
			else if (ret)
			{
				write(2, "error\n", 6);
				exit(EXIT_FAILURE);
			}
			else
				exit(EXIT_SUCCESS);
			restore_stdin_stdout(backup);
		}
		i++;
	}
	ft_closefd(2 * pipecount, fd);
	while (i--)
		wait(NULL);
}