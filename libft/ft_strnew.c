/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:08:28 by cjamal            #+#    #+#             */
/*   Updated: 2019/03/30 09:08:29 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*new;
	size_t	i;

	if ((new = (char*)malloc(sizeof(*new) * (int)size + 1)))
	{
		i = -1;
		while (++i < size + 1)
			*new++ = 0;
		return (new - size - 1);
	}
	return (NULL);
}
