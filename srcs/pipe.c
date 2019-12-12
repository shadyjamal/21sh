#include "../includes/minishell.h"
#include <stdio.h>

int main(int ac, char **av, char **environ)
{
        int     fd[2];
        pid_t   childpid;
        char **cmd;
        char **cmd1;

        cmd = (char**)malloc(sizeof(char*) * 2);
        cmd1 = (char**)malloc(sizeof(char*) * 3);
        cmd1[0] = "/usr/bin/grep";
        cmd1[1] = "cd";
        cmd1[2] = 0;
        cmd[0] = "/bin/ls";
        cmd[1] = 0;
        pipe(fd);
       
        if ((childpid = fork()) == -1)
                exit(1);
        else if (childpid == 0) //ls
        {
                /* Child process closes up input side of pipe "read descriptor" */
                close(fd[1]); //
                dup2(fd[0], 0);
                /* Send "string" through the output side of pipe */
                execve(cmd[0], cmd, NULL);
                //write(fd[1], string, (strlen(string)+1));
                exit(0);
        }
        else // grep
        {
                /* Parent process closes output side of pipe "write descriptor*/
                close(fd[1]);
                dup2(fd[0], 0);
                /* Read in a string from the pipe */
                //nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                execve(cmd1[0], cmd1, NULL);
                //printf("Received string: %s", readbuffer);
        }
        return(0);
}