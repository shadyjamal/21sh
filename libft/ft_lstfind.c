/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 18:11:34 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/26 10:58:26 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**ft_lstfind(t_list **lst, const char *needle, size_t size)
{
	t_list **ptr;

	ptr = lst;
	if (!needle || !size || !lst)
		return (NULL);
	while (*ptr)
	{
		if ((*ptr)->content_size >= size &&
				!ft_memcmp((*ptr)->content, needle, size))
			return (ptr);
		ptr = &(*ptr)->next;
	}
	return (NULL);
}
