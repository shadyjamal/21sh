/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:07:09 by cjamal            #+#    #+#             */
/*   Updated: 2019/04/02 12:47:33 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*cpy;
	int		size;

	size = ft_strlen((char*)str);
	if (!(cpy = (char*)malloc(sizeof(*cpy) * size + 1)))
		return (NULL);
	while ((*cpy++ = *str++))
		;
	return ((char*)cpy - size - 1);
}
