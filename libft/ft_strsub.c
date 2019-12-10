/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:09:05 by cjamal            #+#    #+#             */
/*   Updated: 2019/04/02 12:53:58 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*tronc;
	int		len_cpy;

	tronc = ft_strnew(len);
	len_cpy = len;
	if (s)
	{
		if (tronc)
		{
			while (len_cpy--)
			{
				*tronc++ = *(s + start);
				s++;
			}
			return (tronc - len);
		}
	}
	return (NULL);
}
