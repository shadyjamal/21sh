#include "minishell.h"

t_redirs *ft_create_redirection(t_list *redir)
{
    t_redirs *new_redir;
    t_list *word;

    new_redir = (t_redirs *)malloc(sizeof(t_redirs));
    if (redir)
    {
        word = redir->next;
        new_redir->word = (char *)malloc(sizeof(char) * word->content_size);
        if (ft_strequ(redir->content, ">"))
        {
            new_redir->typeredir = REDIR_OUT;
            new_redir->n = 1;
        }
        else if (ft_strequ(redir->content, "<"))
        {
            new_redir->typeredir = REDIR_IN;
            new_redir->n = 0;
        }
        else if (ft_strequ(redir->content, ">>"))
        {    
            new_redir->typeredir = APPEND_OUT;
            new_redir->n = 1;
        }
        else if (ft_strequ(redir->content, "<<"))
        {
            new_redir->typeredir = HEREDOC;
            new_redir->n = 0;
        }
        ft_memcpy(new_redir->word, word->content, word->content_size);
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
    return ((ft_strequ(str, "|") || ft_strequ(str, ";") || ft_strequ(str, "&&") || ft_strequ(str, "||")));
}

void ft_parse_redirection(t_list **lstcmd, t_redirs **tabredir)
{
    t_list *newlst;
    const char *tmp;
    int j;

    j = 0;
    newlst = *lstcmd;
    tabredir[j] = NULL;
    while (newlst)
    {
        if (newlst->next && !ft_issep_or_and(newlst->next->content))
        {
            tmp = ft_skip_unitl_char(newlst->next->content, "<>");
            if (*tmp)
            {
                ft_lstredirspback(&tabredir[j], ft_create_redirection(newlst->next));
                ft_lstonedel(&newlst->next->next);
                ft_lstonedel(&newlst->next);
            }
            else
                newlst = newlst->next;
        }
        else
        {
            if (!tabredir[j])
                ft_lstredirspback(&tabredir[j], ft_create_redirection(NULL));
            j++;
            tabredir[j] = NULL;
            newlst = newlst->next;
        }
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
    tab_redir = (t_redirs **)malloc(sizeof(t_redirs *) * count + 1);
    ft_parse_redirection(lstcmd, tab_redir);
    return (tab_redir);
}
