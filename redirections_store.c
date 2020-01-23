
#include "minishell.h"

t_redirs	*ft_lstredirspback(t_redirs **blst, t_redirs *newnode)
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

int			ft_issep_or_and(char *str)
{
	return ((ft_strequ(str, "|") || ft_strequ(str, ";")
			|| ft_strequ(str, "&&") || ft_strequ(str, "||")));
}

void		redirection_found(t_list ***lstcmd, t_redirs **tab, int ind)
{
	const char	*tmp;
	t_list		**newlst;

	if (lstcmd && *lstcmd)
	{
		newlst = *lstcmd;
		tmp = ft_skip_unitl_char((*newlst)->content, "<>", NULL);
		if (*tmp)
		{
			ft_lstredirspback(&tab[ind], ft_create_redir(*newlst, (char *)tmp));
			ft_lstonedel(&(*newlst)->next);
			ft_lstonedel(newlst);
		}
		else
			*lstcmd = &(*newlst)->next;
	}
}

void		ft_parse_redirection(t_list **lstcmd, t_redirs **tab)
{
	t_list		**newlst;
	int			j;

	j = 0;
	newlst = lstcmd;
	while (*newlst)
	{
		if (!ft_issep_or_and((*newlst)->content))
			redirection_found(&newlst, tab, j);
		else
		{
			if (!tab[j])
				ft_lstredirspback(&tab[j], ft_create_redir(NULL, NULL));
			j++;
			newlst = &(*newlst)->next;
		}
		if (!*newlst && !tab[j])
			ft_lstredirspback(&tab[j], ft_create_redir(NULL, NULL));
	}
}

t_redirs	**ft_alloc_tabredirs(t_list **lstcmd)
{
	t_redirs	**tab_redir;
	t_list		*tmplst;
	int			cnt;

	tab_redir = NULL;
	if (lstcmd)
	{
		tmplst = *lstcmd;
		cnt = 1;
		while (tmplst)
		{
			if (ft_issep_or_and(tmplst->content))
				cnt++;
			tmplst = tmplst->next;
		}
		if (!(tab_redir = (t_redirs **)malloc(sizeof(t_redirs *) * (cnt + 1))))
			return (NULL);
		ft_memset(tab_redir, 0, sizeof(t_redirs *) * (cnt + 1));
		ft_parse_redirection(lstcmd, tab_redir);
	}
	return (tab_redir);
}
