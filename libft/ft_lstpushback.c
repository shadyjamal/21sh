/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:05:19 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/19 19:01:28 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpushback(t_list **blst, void const *content,
		size_t content_size)
{
	t_list	*list;

	if (!blst || !content_size)
		return (NULL);
	list = *blst;
	if (list)
	{
		while (list && list->next)
			list = list->next;
		list->next = ft_lstnew(content, content_size);
		return (list->next);
	}
	else
	{
		*blst = ft_lstnew(content, content_size);
		return (*blst);
	}
}
