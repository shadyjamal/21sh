/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitmultiply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:59:08 by cjamal            #+#    #+#             */
/*   Updated: 2019/04/09 17:47:34 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_bitmultiply(unsigned int a, unsigned int b)
{
	int res;

	res = 0;
	while (b > 0)
	{
		if (b & 1)
			res = res + a;
		a = a << 1;
		b = b >> 1;
	}
	return (res);
}
