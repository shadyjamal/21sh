/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 00:49:37 by cjamal            #+#    #+#             */
/*   Updated: 2020/01/24 01:07:02 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	save_stdin_stdout(int *std)
{
	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	std[2] = dup(STDERR_FILENO);
}

void	restore_stdin_stdout(int *std)
{
	dup2(std[0], STDIN_FILENO);
	close(std[0]);
	dup2(std[1], STDOUT_FILENO);
	close(std[1]);
	dup2(std[2], STDERR_FILENO);
	close(std[2]);
}
