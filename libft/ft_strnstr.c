/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:08:35 by cjamal            #+#    #+#             */
/*   Updated: 2019/04/09 13:56:03 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t size;

	size = ft_strlen((char*)to_find);
	if (!size)
		return ((char*)str);
	while (*str && len)
	{
		if (*str == *to_find)
		{
			if (ft_strnequ(str, to_find, size) && size <= len)
				return ((char*)str);
		}
		str++;
		len--;
	}
	return (NULL);
}
