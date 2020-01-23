
#include "minishell.h"

void	ft_closefd(int fdcount, int *fd)
{
	int i;

	i = 0;
	while (i < fdcount)
	{
		close(fd[i]);
		i++;
	}
}

void	ft_pipefd(int *fd, int pipecount)
{
	int i;

	i = 0;
	while (i < pipecount)
	{
		pipe(&fd[2 * i]);
		i++;
	}
}

pid_t	fork_process(void)
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
