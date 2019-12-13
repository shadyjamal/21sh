#include "../includes/minishell.h"
#include <stdio.h>
#include <fcntl.h>

void execpipe(char ***cmd)
{
        int     fd[2];
        pid_t   childpid;
        int     fd_in = 0;
        int     i;

        i = 0;
        while (*cmd != NULL)
        {
                pipe(fd);
                if ((childpid = fork()) == -1)
                        printf("fork error");
                else if (childpid == 0)
                {
                        dup2(fd_in, 0);
                        if (*(cmd + 1) != NULL) // if there is a next cmd
                                dup2(fd[1], 1);
                        close(fd[0]);
                        close(fd[1]);
                        if (execve((*cmd)[0], *cmd, NULL) == -1)
                                exit(EXIT_FAILURE);
                }
                else 
                {
                        wait(NULL);
                        close(fd[1]);
                        if (fd_in)
                                close(fd_in);
                        fd_in = fd[0];
                        cmd++;
                }
        }
}

void    ft_redirect(char ***cmd, char *fdin, char *fdout)
{
        int in;
        int out;

        in = fdin ? open(fdin, O_RDONLY) : 0;
        out = fdout ? open(fdout, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR) : 1;
        // replace standard input with input file
        dup2(in, 0);
        // replace standard output with output file
        dup2(out, 1);
        close(in);
        close(out);
        execpipe(cmd);
}

int main ()
{
        char fdin[] = "test";
        char fdout[] = "";
        //char *ls[] = {"/bin/ls", NULL};
        char *grep[] = {"/usr/bin/grep", "chadi", NULL};
        //char *wc[] = {"/usr/bin/wc","-c", NULL};
        //char *cat[] = {"/bin/cat", NULL};
        char **cmd[] = {grep, NULL};

        ft_redirect(cmd, fdin, fdout);
        //execpipe(cmd);
        return (0);
}