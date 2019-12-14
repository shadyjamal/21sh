#include "../includes/minishell.h"
#include <stdio.h>
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

void    ft_execpipe(char ***cmd, int pipecount)
{
        int fd[2 * pipecount];
        pid_t parrentpid;
        pid_t childpid;
        int i;

        if ((parrentpid = fork()) == -1)
                printf("fork error");
        else if (parrentpid == 0)
        {
                ft_pipefd(fd, pipecount); /* Initialize pipes */
                i = 0;
                while (cmd[i + 1] != NULL)
                {
                        if ((childpid = fork()) == -1)
                                printf("fork error");
                        else if (childpid == 0)
                        {
                                if (i != 0)
                                        dup2(fd[2 * (i - 1)], 0);
                                dup2(fd[2 * i + 1], 1); 
                                ft_closefd(2 * pipecount, fd); /* Close all fd */
                                if (execve(cmd[i][0], cmd[i], NULL) == -1)
                                        exit(EXIT_FAILURE);
                        }
                        i++;
                }
                if (i)
                        dup2(fd[2 * (i - 1)], 0);
                ft_closefd(2 * pipecount, fd);
                if (execve(cmd[i][0], cmd[i], NULL) == -1)
                        exit(EXIT_FAILURE);
        }
        else
                wait(NULL);
}

void ft_redirect(char ***cmd, char *fdin, char *fdout)
{
        int in;
        int out;

        in = fdin ? open(fdin, O_RDONLY) : 0;
        out = fdout ? open(fdout, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR) : 1;
        dup2(in, 0);  // replace standard input with input file
        dup2(out, 1); // replace standard output with output file
        close(in);
        close(out);
        ft_execpipe(cmd, 2);
}

int main()
{
        char fdin[] = "test";
        char fdout[] = "hello";
        //char *ls[] = {"/bin/ls", "-lR", "/", NULL};
        char *grep[] = {"/usr/bin/grep", "chadi", NULL};
        //char *pwd[] = {"/bin/pwd", NULL};
        //char *echo[] = {"/bin/echo", "sdcascv", NULL};
        //char *wc[] = {"/usr/bin/wc","-c", NULL};
        char *cat[] = {"/bin/cat", "test", NULL};
        char **cmd[] = {cat, grep, NULL};

        ft_redirect(cmd, fdin, fdout);
        //ft_execpipe(cmd, 2);
        return (0);
}