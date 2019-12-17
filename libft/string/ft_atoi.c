/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:53:01 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/07/31 16:16:25 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define WS(c) ft_iswhitespace(c)

long long	ft_atoi(const char *s)
{
	long long	n;
	int			m;
	int			i;

	n = 0;
	i = 0;
	m = 1;
	while (WS(*s) || ((*s == 45 || *s == 43) && ft_isdigit(s[1])))
		m *= (*s++ == '-' ? -1 : 1);
	while (i++ < 19 && ft_isdigit(*s))
		n = (n * 10) + (*s++ - '0');
	return (n * m);
}
