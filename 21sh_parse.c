#include "minishell.h"

int ft_ltrcount(char **cmd, char *ltr)
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

int ft_logiccount(char **cmd)
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

char ***parsesep(char **cmd, int sep_count, char *sep, int *size_sep)
{
	int i;
	int j;
	char ***tab;

	tab = NULL;
	if (cmd && (tab = (char ***)malloc(sizeof(char **) * (sep_count + 2))))
	{
		ft_memset(tab, 0, sizeof(char **) * (sep_count + 2));
		j = 0;
		i = 0;
		while (cmd[i])
		{
			if (!ft_strequ(cmd[i], sep))
				tab[j++] = &cmd[i];
			else
				tab[j++] = 0;
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

char ***parse_or_and(char **cmd, int count, t_list **logic)
{
	int i;
	int j;
	char ***tab;

	tab = NULL;
	*logic = NULL;
	if (count && cmd && (tab = (char ***)malloc(sizeof(char **) * (count + 2))))
	{
		ft_memset(tab, 0, sizeof(char **) * (count + 2));
		j = 0;
		i = 0;
		while (cmd[i])
		{
			if (!ft_strequ(cmd[i], "&&") && !ft_strequ(cmd[i], "||"))
				tab[j++] = &cmd[i];
			else
				tab[j++] = 0;
			while (cmd[i] && !ft_strequ(cmd[i], "&&") && !ft_strequ(cmd[i], "||"))
				i++;
			if (cmd[i])
			{
				ft_strequ(cmd[i], "&&") ? ft_lstpushback(logic, "&&", 3) : ft_lstpushback(logic, "||", 3);
				free(cmd[i]);
				cmd[i] = 0;
				i++;
			}
		}
	}
	return (tab);
}
