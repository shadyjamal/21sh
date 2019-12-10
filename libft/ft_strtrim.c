/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:09:11 by cjamal            #+#    #+#             */
/*   Updated: 2019/04/02 17:47:10 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	iswhitespace(char c)
{
	if (((c == ' ' || c == '\t') || c == '\n') && c)
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	char	*trim;
	int		i;
	int		j;
	int		size;

	if (s)
	{
		size = 0;
		i = -1;
		j = ft_strlen((char*)s);
		while (iswhitespace(s[++i]))
			;
		if (i < j)
			while (iswhitespace(s[--j]))
				;
		size = j - i + 1;
		if (i <= j)
			if ((trim = ft_strnew(size)))
				return (ft_strsub(s, i, size));
	}
	return (NULL);
}
