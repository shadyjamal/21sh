#include "minishell.h"

char *ft_strjoin_free(char const *s1, char const *s2, int i)
{
	char *str;

	str = ft_strjoin(s1, s2);
	if (i == 1)
		ft_strdel((char **)&s1);
	if (i == 2)
		ft_strdel((char **)&s2);
	if (i == 3)
	{
		ft_strdel((char **)&s1);
		ft_strdel((char **)&s2);
	}
	return (str);
}

char *prompt_heredoc(char *eof, int *fd)
{
	char *cmd;
	char *entry;

	entry = ft_strnew(0);
	while (42)
	{
		ft_putchar_fd('>', fd[1]);
		if (get_next_line(fd[0], &cmd) > 0)
		{
			if (ft_strcmp(cmd, eof) == 0)
			{
				free(cmd);
				break ;
			}
			entry = ft_strjoin_free(entry, ft_strjoin_free(cmd, "\n", 1), 3);
		}
	}
	return (entry);
}

int exec_heredoc(char *eof, int *fd)
{
	char *entry;
	int herefd[2];

	entry = prompt_heredoc(eof, fd);
	pipe(herefd);
	// if (fork_process() == 0)
	// {
	// 	close(fd[0]);
	// 	ft_putstr_fd(entry, fd[1]);
	// 	ft_strdel(&entry);
	// 	exit(1);
	// }
	// wait(NULL);
	ft_putstr_fd(entry, herefd[1]);
	close(herefd[1]);
	return (herefd[0]);
}

int open_fileredir(int typeredir, char *word, int *fd)
{
	if (typeredir == REDIR_OUT)
		return (open(word, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR));
	else if (typeredir == APPEND_OUT)
		return (open(word, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR));
	else if (typeredir == REDIR_IN)
		return (open(word, O_RDONLY));
	else
		return (exec_heredoc(word, fd));
}

void ft_exec_redirections(t_redirs *tabredir, int *fd)
{
	int file_fd;

	while (tabredir && tabredir->typeredir != NO_REDIR)
	{
		file_fd = open_fileredir(tabredir->typeredir, tabredir->word, fd);
		if (file_fd < 0)
		{
			ft_putendl_fd("error", 2);
			exit(0);
		}
		dup2(file_fd, tabredir->n);
		close(file_fd);
		tabredir = tabredir->next;
	}
}