/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:07:43 by cjamal            #+#    #+#             */
/*   Updated: 2019/04/02 12:48:05 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	len_dest;
	int		i_buffer;
	size_t	len_src;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen((char*)src);
	if (n <= len_dest)
		return (len_src + n);
	i_buffer = n - len_dest;
	dest += len_dest;
	while (*src && i_buffer-- > 1)
		*dest++ = *src++;
	*dest = '\0';
	return (len_dest + len_src);
}
