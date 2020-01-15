
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

char *prompt_heredoc(char *eof)
{
	char *cmd;
	char *entry;

	entry = ft_strnew(0);
	while (42)
	{
		ft_putchar('>');
		if (get_next_line(0, &cmd) > 0)
		{
			if (ft_strcmp(cmd, eof) == 0)
			{
				free(cmd);
				break;
			}
			entry = ft_strjoin_free(entry, ft_strjoin_free(cmd, "\n", 1), 3);
		}
	}
	return (entry);
}

void which_redirection_out(t_redirs *new, char *idx_redir)
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
void which_redirection_in(t_redirs *new, char *idx_redir)
{
	if (ft_strequ(idx_redir + 1, ""))
		new->typeredir = REDIR_IN;
	else if (ft_strequ(idx_redir + 1, "<"))
	{
		new->typeredir = HEREDOC;
		new->word = prompt_heredoc(new->word);
	}
	else if (ft_strequ(idx_redir + 1, "&"))
		new->typeredir = DUPLIC_IN;
	if (new->n < 0)
		new->n = 0;
}

t_redirs *ft_create_redir(t_list *redir, char *idx_redir)
{
	t_redirs *new_redir;
	t_list *word;

	if (!(new_redir = (t_redirs *)malloc(sizeof(t_redirs))))
		return (NULL);
	new_redir->n = -1;
	if (redir && redir->next)
	{
		word = redir->next;
		new_redir->word = (char *)malloc(word->content_size);
		ft_memcpy(new_redir->word, word->content, word->content_size);
		if (idx_redir > (char *)redir->content)
			new_redir->n = ft_atoi(redir->content);
		if (*idx_redir == '>')
			which_redirection_out(new_redir, idx_redir);
		else if (*idx_redir == '<')
			which_redirection_in(new_redir, idx_redir);
	}
	else
	{
		new_redir->typeredir = NO_REDIR;
		new_redir->word = ft_strdup("");
	}
	new_redir->next = NULL;
	return (new_redir);
}

t_redirs *ft_lstredirspback(t_redirs **blst, t_redirs *newnode)
{
	t_redirs *list;

	if (!blst)
		return (NULL);
	list = *blst;
	if (list)
	{
		while (list && list->next)
			list = list->next;
		list->next = newnode;
		return (list->next);
	}
	else
	{
		*blst = newnode;
		return (*blst);
	}
}

int ft_issep_or_and(char *str)
{
	return ((ft_strequ(str, "|") || ft_strequ(str, ";")
	|| ft_strequ(str, "&&") || ft_strequ(str, "||")));
}

void ft_parse_redirection(t_list **lstcmd, t_redirs **tabredir)
{
	t_list **newlst;
	const char *tmp;
	int j;

	j = 0;
	newlst = lstcmd;
	while (*newlst)
	{
		if (!ft_issep_or_and((*newlst)->content))
		{
			tmp = ft_skip_unitl_char((*newlst)->content, "<>");
			if (*tmp)
			{
				ft_lstredirspback(&tabredir[j], ft_create_redir(*newlst, (char *)tmp));
				ft_lstonedel(&(*newlst)->next);
				ft_lstonedel(newlst);
			}
			else
				newlst = &(*newlst)->next;
		}
		else
		{
			if (!tabredir[j])
				ft_lstredirspback(&tabredir[j], ft_create_redir(NULL, NULL));
			j++;
			newlst = &(*newlst)->next;
		}
		if (!*newlst && !tabredir[j])
			ft_lstredirspback(&tabredir[j], ft_create_redir(NULL, NULL));
	}
}

t_redirs **ft_alloc_tabredirs(t_list **lstcmd)
{
	t_redirs **tab_redir;
	t_list *tmplst;
	int count;

	tmplst = *lstcmd;
	count = 1;
	while (tmplst)
	{
		if (ft_issep_or_and(tmplst->content))
			count++;
		tmplst = tmplst->next;
	}
	if (!(tab_redir = (t_redirs **)malloc(sizeof(t_redirs *) * (count + 1))))
		return (NULL);
	ft_memset(tab_redir, 0, sizeof(t_redirs *) * (count + 1));
	ft_parse_redirection(lstcmd, tab_redir);
	return (tab_redir);
}
