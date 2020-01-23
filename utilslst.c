#include "minishell.h"

t_list	*tab_to_list(char **env)
{
	int		i;
	int		len;
	t_list	*head;

	i = 0;
	len = 0;
	head = NULL;
	while (env[i])
	{
		len = ft_strlen(env[i]);
		ft_strreplace(env[i], '=', 0);
		ft_lstpushback(&head, env[i], len + 1);
		ft_strreplace(env[i], '\0', '=');
		i++;
	}
	return (head);
}

char	**list_to_tab(t_list *lst, int flag)
{
	char	**tab_lst;
	int		i;

	tab_lst = (char **)ft_memalloc(sizeof(char *) * (ft_lstsize(lst, 0) + 1));
	i = 0;
	while (lst && tab_lst)
	{
		if (!lst->content)
			lst = lst->next;
		else if ((tab_lst[i] = (char *)malloc(lst->content_size)))
		{
			flag ? ft_strreplace(lst->content, 0, '=') : 0;
			ft_memcpy(tab_lst[i++], lst->content, lst->content_size);
			flag ? ft_strreplace(lst->content, '=', 0) : 0;
			lst = lst->next;
		}
		else
		{
			ft_free_2d_tab(tab_lst);
			return (NULL);
		}
	}
	return (tab_lst);
}

void	ft_lstonedel(t_list **to_del)
{
	t_list	*tmp;

	if (to_del && *to_del)
	{
		tmp = *to_del;
		*to_del = tmp->next;
		free(tmp->content);
		free(tmp);
	}
}

void	ft_lstmodifone(t_list *to_mod, char *value)
{
	free(to_mod->content);
	to_mod->content = value;
	to_mod->content_size = ft_strlen(value) + 1;
}

void	ft_display_prompt(char *ptr, int error)
{
	char	*path;
	char	color[6];

	if (!ptr)
	{
		ft_strcpy(prompt, "\e[91m➜\e[0m  🤔 🤔  ");
		return ;
	}
	error ? ft_strcpy(color, "\e[91m") : ft_strcpy(color, "\e[92m");
	path = ft_strrchr(ptr + 4 + (ptr[4] != 0), '/');
	if (path && *path)
		path += 1;
	else
		path = ptr + 4;
	ft_strcpy(prompt, color);
	ft_strcat(prompt, "➜\e[0m  \e[1m\e[96m");
	ft_strcat(prompt, path);
	ft_strcat(prompt, "\e[0m ");
}
