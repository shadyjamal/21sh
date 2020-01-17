#include "minishell.h"

int	exec_heredoc(char *entry)
{
	int herefd[2];

	pipe(herefd);
	ft_putstr_fd(entry, herefd[1]);
	close(herefd[1]);
	return (herefd[0]);
}

int	open_fileredir(t_redirs *redir)
{
	if (redir->typeredir == REDIR_OUT)
		return (open(redir->word, O_TRUNC | O_WRONLY | O_CREAT, FLAGS));
	else if (redir->typeredir == APPEND_OUT)
		return (open(redir->word, O_APPEND | O_WRONLY | O_CREAT, FLAGS));
	else if (redir->typeredir == REDIR_IN)
		return (open(redir->word, O_RDONLY));
	else if (redir->typeredir == DUPLIC_OUT || redir->typeredir == DUPLIC_IN)
	{
		if (ft_strequ(redir->word, "-"))
			return (close(redir->n));
		else
			return ((int)ft_atoi(redir->word));
	}
	else
		return (exec_heredoc(redir->word));
}

int	file_access(char *cmd)
{
	if (cmd && !ft_is_dir(cmd) && !access(cmd, F_OK))
	{
		if (access(cmd, R_OK) || access(cmd, W_OK))
			return (-1);
		else
			return (1);
	}
	return (0);
}

int	ft_exec_redirections(t_redirs *redir)
{
	int file_fd;
	int ret;

	while (redir && redir->typeredir != NO_REDIR)
	{
		file_fd = open_fileredir(redir);
		if (file_fd < 0)
		{
			ret = file_access(redir->word);
			if (!ret && ft_is_dir(redir->word))
				PRINT_ERROR(redir->word, IS_DIR);
			else if (ret < 0)
				PRINT_ERROR(redir->word, PERM_DENYD);
			return (1);
		}
		if (!(((redir->typeredir == DUPLIC_OUT
		|| redir->typeredir == DUPLIC_IN)) && ft_strequ(redir->word, "-")))
		{
			dup2(file_fd, redir->n);
			if (file_fd != redir->n)
				close(file_fd);
		}
		redir = redir->next;
	}
	return (0);
}
