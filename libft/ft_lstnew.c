/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:04:35 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/18 17:03:35 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*node;

	node = (t_list*)malloc(sizeof(t_list));
	if (node)
	{
		if (!(content))
		{
			node->content = NULL;
			node->content_size = 0;
		}
		else
		{
			node->content = malloc(sizeof(*(node->content)) * content_size);
			if (!(node->content))
				return (NULL);
			node->content = ft_memcpy(node->content, content, content_size);
			node->content_size = content_size;
		}
		node->next = NULL;
		return (node);
	}
	return (NULL);
}
