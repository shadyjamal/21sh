#include "minishell.h"

int		ft_ltrcount(char **cmd, char *ltr)
{
	int i;
	int sepcount;

	i = 0;
	sepcount = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			if (!ft_strcmp(cmd[i], ltr))
				sepcount += 1;
			i++;
		}
	}
	return (sepcount);
}

int		ft_logiccount(char **cmd)
{
	int i;
	int sepcount;

	i = 0;
	sepcount = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			if (!ft_strcmp(cmd[i], "&&") || !ft_strcmp(cmd[i], "||"))
				sepcount += 1;
			i++;
		}
	}
	return (sepcount);
}

char	***parsesep(char **cmd, int sep_count, char *sep, int *size_sep)
{
	int		i;
	int		j;
	char	***tab;

	tab = NULL;
	if (cmd && (tab = (char ***)ft_memalloc(sizeof(char **) * (sep_count + 2))))
	{
		j = 0;
		i = 0;
		while (cmd[i])
		{
			tab[j++] = !ft_strequ(cmd[i], sep) ? &cmd[i] : 0;
			while (cmd[i] && !ft_strequ(cmd[i], sep))
				i++;
			if (cmd[i])
			{
				free(cmd[i]);
				cmd[i] = 0;
				i++;
			}
		}
		if (ft_strequ(sep, ";"))
			*size_sep = j ? j : !j;
	}
	return (tab);
}

char	***parse_or_and(char **cm, int cnt, t_list **logic)
{
	int		i;
	int		j;
	char	***tab;

	tab = NULL;
	*logic = NULL;
	if (cnt && cm && (tab = (char ***)ft_memalloc(sizeof(char **) * (cnt + 2))))
	{
		j = 0;
		i = 0;
		while (cm[i])
		{
			tab[j++] = ft_strequ(cm[i], "&&") ||
						ft_strequ(cm[i], "||") ? 0 : &cm[i];
			while (cm[i] && !ft_strequ(cm[i], "&&") && !ft_strequ(cm[i], "||"))
				i++;
			if (cm[i])
			{
				ft_lstpushback(logic, ft_strequ(cm[i], "&&") ? "&&" : "||", 3);
				free(cm[i]);
				cm[i++] = 0;
			}
		}
	}
	return (tab);
}
