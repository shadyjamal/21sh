/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:08:00 by cjamal            #+#    #+#             */
/*   Updated: 2019/04/02 12:49:05 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*t;
	size_t	size;
	int		i;

	if (!s || !f)
		return (NULL);
	size = ft_strlen((char*)s);
	if (!(t = (char*)malloc(sizeof(*s) * size + 1)))
		return (NULL);
	i = -1;
	while (*s)
		*t++ = f(++i, *s++);
	*t = '\0';
	return (t - size);
}
