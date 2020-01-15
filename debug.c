#include "minishell.h"

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

void printlst(t_list *lst)
{
    while (lst)
    {
        ft_putendl(lst->content);
        lst = lst->next;
    }
    ft_putendl("Endoflst");
}

void printlstredirs(t_redirs **tabredir)
{
    int i = 0;
    t_redirs    *beginredir;

    while (tabredir[i])
    {
        beginredir = tabredir[i];
        ft_putstr("*** Redirections of CMD ");
        ft_putnbr(i + 1);
        ft_putchar('\n');
        while (beginredir)
        {
            ft_putstr("file redirected to= ");
            ft_putendl(beginredir->word);
            ft_putstr("type of redirection = ");
            ft_putnbr(beginredir->typeredir);
            ft_putchar('\n');
            ft_putstr("FD redirected = ");
            ft_putnbr(beginredir->n);
            ft_putchar('\n');
            beginredir = beginredir->next;
        }
        i++;
    }
}
