/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:08:42 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/29 15:43:14 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*t;

	if (!s)
		return (NULL);
	if (!c)
		return ((char*)s + ft_strlen((char*)s));
	t = NULL;
	while (*s++)
		if (*(s - 1) == c)
			t = (char *)(s - 1);
	return (t);
}
