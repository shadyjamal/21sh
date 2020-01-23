
#include "minishell.h"

int ft_str_isdigit(const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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
		return (open(redir->word, O_TRUNC | O_WRONLY | O_CREAT, 0644));
	else if (redir->typeredir == APPEND_OUT)
		return (open(redir->word, O_APPEND | O_WRONLY | O_CREAT, 0644));
	else if (redir->typeredir == REDIR_IN)
		return (open(redir->word, O_RDONLY));
	else if (redir->typeredir == DUPLIC_OUT || redir->typeredir == DUPLIC_IN)
	{
		if (ft_strequ(redir->word, "-"))
		{
			close(redir->n);
			return (CLOSED_FD);
		}
		if (ft_str_isdigit(redir->word))
			return ((int)ft_atoi(redir->word));
		else if (redir->typeredir == DUPLIC_IN)
			return (-2);
		else if (redir->typeredir == DUPLIC_OUT && redir->n != 1)
			return (-2);
		else
			return (open(redir->word, O_TRUNC | O_WRONLY | O_CREAT, 0644));			
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
		if ((file_fd = open_fileredir(redir)) < 0)
		{
			if (file_fd == -2)
				return (PRINT_ERROR(redir->word, AMB_REDIR));
			if (!(ret = file_access(redir->word)) && ft_is_dir(redir->word))
				return (PRINT_ERROR(redir->word, IS_DIR));
			else if (ret < 0)
				return (PRINT_ERROR(redir->word, PERM_DENYD));
		}
		if (file_fd != CLOSED_FD)
		{
			if (dup2(file_fd, redir->n) < 0)
				return (PRINT_ERROR(redir->word, BAD_FD));
			if (redir->typeredir == DUPLIC_OUT && !ft_str_isdigit(redir->word))
				dup2(redir->n, 2);
			(file_fd != redir->n) ? close(file_fd) : 0;
		}
		redir = redir->next;
	}
	return (0);
}
