/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:07:35 by cjamal            #+#    #+#             */
/*   Updated: 2019/04/02 12:50:03 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concat;

	if (!s1 || !s2)
		return (NULL);
	if ((concat = ft_strnew(ft_strlen((char*)s1) + ft_strlen((char*)s2))))
	{
		if (s1)
			concat = ft_strcat(concat, (char*)s1);
		if (s2)
			concat = ft_strcat(concat, (char*)s2);
		return (concat);
	}
	return (NULL);
}
