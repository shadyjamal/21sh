
#include "minishell.h"

char		*ft_strjoin_free(char const *s1, char const *s2, int i)
{
	char	*str;

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

char		*prompt_heredoc(char *eof)
{
	char	*cmd;
	char	*entry;

	entry = ft_strnew(0);
	while (42)
	{
		if ((cmd = ft_readline("> ")))
		{
			if ((!ft_strcmp(cmd, eof)) || (*cmd == '\4'))
			{
				free(cmd);
				break ;
			}
			entry = ft_strjoin_free(entry, ft_strjoin_free(cmd, "\n", 1), 3);
		}
	}
	return (entry);
}

void		which_redirection_out(t_redirs *new, char *idx_redir)
{
	if (ft_strequ(idx_redir + 1, ""))
		new->typeredir = REDIR_OUT;
	else if (ft_strequ(idx_redir + 1, ">"))
		new->typeredir = APPEND_OUT;
	else if (ft_strequ(idx_redir + 1, "&"))
		new->typeredir = DUPLIC_OUT;
	if (new->n < 0)
		new->n = 1;
}

void		which_redirection_in(t_redirs *new, char *idx_redir)
{
	char	*tmp;

	if (ft_strequ(idx_redir + 1, ""))
		new->typeredir = REDIR_IN;
	else if (ft_strequ(idx_redir + 1, "<"))
	{
		new->typeredir = HEREDOC;
		tmp = prompt_heredoc(new->word);
		ft_strdel(&new->word);
		new->word = tmp;
	}
	else if (ft_strequ(idx_redir + 1, "&"))
		new->typeredir = DUPLIC_IN;
	if (new->n < 0)
		new->n = 0;
}

t_redirs	*ft_create_redir(t_list *occur, char *idx_redir)
{
	t_redirs	*redir;

	if (!(redir = (t_redirs *)malloc(sizeof(t_redirs))))
		return (NULL);
	redir->n = -1;
	if (occur && occur->next)
	{
		redir->word = (char *)ft_memalloc(occur->next->content_size);
		ft_memcpy(redir->word, occur->next->content, occur->next->content_size);
		if (idx_redir > (char *)occur->content)
			redir->n = ft_atoi(occur->content);
		if (*idx_redir == '>')
			which_redirection_out(redir, idx_redir);
		else if (*idx_redir == '<')
			which_redirection_in(redir, idx_redir);
	}
	else
	{
		redir->typeredir = NO_REDIR;
		redir->word = ft_strdup("");
	}
	redir->next = NULL;
	return (redir);
}
