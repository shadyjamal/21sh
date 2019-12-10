/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:04:28 by cjamal            #+#    #+#             */
/*   Updated: 2019/04/02 12:22:47 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*first;

	if (!lst || !f)
		return (NULL);
	tmp = f(lst);
	first = tmp;
	while ((lst = lst->next))
	{
		if (tmp != NULL)
		{
			tmp->next = f(lst);
			tmp = tmp->next;
		}
		else
			return (NULL);
	}
	return (first);
}
