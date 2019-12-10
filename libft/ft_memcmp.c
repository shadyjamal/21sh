/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:05:04 by cjamal            #+#    #+#             */
/*   Updated: 2019/04/02 12:39:25 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int ret;

	ret = 0;
	if (n)
		while ((ret = *(unsigned char *)s1++ - *(unsigned char *)s2++) == 0
				&& --n)
			;
	return (ret);
}
