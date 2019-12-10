/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:05:26 by cjamal            #+#    #+#             */
/*   Updated: 2019/03/30 09:05:27 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	if (dest < src)
		return (ft_memcpy(dest, src, len));
	else if (dest > src)
	{
		dest += len;
		src += len;
		while (len--)
			*(char*)--dest = *(char*)--src;
	}
	return (dest);
}
