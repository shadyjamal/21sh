/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:07:55 by cjamal            #+#    #+#             */
/*   Updated: 2019/04/02 12:48:23 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*t;
	size_t	size;

	if (!s || !f)
		return (NULL);
	size = ft_strlen((char*)s);
	if ((t = ft_strnew(size)))
	{
		while (*s)
			*t++ = f(*s++);
		return (t - size);
	}
	return (NULL);
}
