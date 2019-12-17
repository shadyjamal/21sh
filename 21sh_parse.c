#include "minishell.h"

int ft_ltrcount(char **cmd, char *ltr)
{
	int i;
	int sepcount;
	
	i = 0;
	sepcount = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], ltr))
			sepcount += 1;
		i++;
	}
	return (sepcount);
}

void printmatrix(char **cmd)
{
    int i = 0;

    while (cmd[i])
    {
        ft_putendl(cmd[i]);
        i++;
    }
    ft_putendl("EndofCmd");
}

char	***parsesep(char **cmd, int sep_count, char *sep)
{
	int i;
	int j;
	char ***tab;
    
    tab = NULL;
	if (cmd)
    {
        tab = (char***)malloc(sizeof(char**) * (sep_count + 2));
	    i = 0;
	    j = 0;
	    tab[j++] = &cmd[i];
        while (cmd[i])
        {
            if (!ft_strcmp(cmd[i], sep))
            {
                cmd[i] = 0;
                tab[j] = &cmd[i + 1];
                j++;
            }
            i++;
        }
        tab[j] = 0;

    }
	return (tab);
}
