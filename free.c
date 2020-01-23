
#include "minishell.h"

void	ft_free_lstredir(t_redirs **alst)
{
	t_redirs *to_free;

	while (*alst)
	{
		to_free = *alst;
		*alst = (*alst)->next;
		ft_strdel(&to_free->word);
		free(to_free);
	}
	*alst = NULL;
}

void	ft_free_tabredir(t_redirs **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_free_lstredir(&tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_cmd(char **tab, int size)
{
	int i;

	i = 0;
	if (tab)
	{
		while (i < size)
		{
			ft_strdel(&tab[i]);
			i++;
		}
		free(tab);
	}
}

void	ft_free(t_cmd_holder *hold)
{
	ft_free_tabredir(hold->tab_redir);
	ft_free_cmd(hold->tabcmd, hold->size_cmd);
	free(hold->tabsep);
}
