#include "minishell.h"
#include <fcntl.h>

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

void    ft_pipefd(int *fd, int pipecount)
{
	int     i;
	
	i = 0;
	while (i < pipecount)
	{
		pipe(&fd[2 * i]);
		i++;
	}
}

void    ft_execpipe(char ***cmd, int pipecount, t_list *env, t_env_var *var)
{
	int     fd[2 * pipecount];
	pid_t   parrentpid;
	pid_t   childpid;
	int     i;
    char    *cmdpath;
    int     ret;

	if ((parrentpid = fork()) == -1)
		printf("fork error");
	else if (parrentpid == 0)
	{
		ft_pipefd(fd, pipecount); /* Initialize pipes */
		i = 0;
		while (cmd[i + 1] != NULL)
		{
            cmdpath = NULL;
			if ((childpid = fork()) == -1)
				printf("fork error");
			else if (childpid == 0)
			{
				dup2(fd[2 * (i - 1)], 0);
				dup2(fd[2 * i + 1], 1); 
				ft_closefd(2 * pipecount, fd); /* Close all fd */
				ret = dispatch(cmd[i], &env, var, &cmdpath);
                if (cmdpath)
				{
                    if (execve(cmdpath, cmd[i], NULL) == -1)
					    exit(EXIT_FAILURE);
                }
                else if (ret)
                    exit(EXIT_FAILURE);
                else 
                    exit(EXIT_SUCCESS);
			}
			i++;
		}
		dup2(fd[2 * (i - 1)], 0);
        ft_closefd(2 * pipecount, fd);
        ret = dispatch(cmd[i], &env, var, &cmdpath);
        if (cmdpath)
		{
            if (execve(cmdpath, cmd[i], NULL) == -1)
			exit(EXIT_FAILURE);
        }
        else if (ret)
            exit(EXIT_FAILURE);
        else 
            exit(EXIT_SUCCESS);
	}
	else
		wait(NULL);
}

// void ft_redirect_out(char *fdout, _Bool append)
// {
// 	int out;

// 	out = 1;
// 	if (fdout)
// 	{
// 		if (!append)
// 		{
// 			if ((out = open(fdout, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) < 0)
// 				return ; // error
// 		}
// 		else
// 		{
// 		     if ((out = open(fdout, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) < 0)
// 				return ; 
// 		}
// 		dup2(out, 1); // replace standard output with output file
// 		close(out);
// 		//printf("ok");
// 	}
// }

// void ft_redirect_in_out(char *filed)
// {
// 	int fd;

// 	fd = 0;
// 	if (filed)
// 	{
// 		if ((fd = open(filed, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) < 0)
// 			return ;
// 		dup2(fd, 1);
// 		//dup2(fd, 2); // replace standard input with input file
// 		close(fd);
// 	}
// }

// void ft_redirect_in(char *fdin)
// {
// 	int in;

// 	in = 0;
// 	if (fdin)
// 	{
// 		if ((in = open(fdin, O_RDONLY)) < 0)
// 			return ;
// 		dup2(in, 0); // replace standard input with input file
// 		close(in);
// 	}
// }