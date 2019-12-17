/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 18:03:34 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/29 14:25:07 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define TR(c, v) ((c) >= 0 ? (c) : (v))

char	**ft_strsplit(char const *s, char *cmp)
{
	int		size;
	int		i;
	char	**tab2d;

	i = 0;
	size = ft_wordcount(s, cmp);
	if (!size || !(tab2d = (char **)ft_memalloc((size + 1) * sizeof(char *))))
		return (0);
	while (size--)
	{
		s = ft_skip_chars(s, cmp);
		tab2d[i + 1] = (char *)ft_skip_unitl_char(s, cmp);
		if (!(tab2d[i] = ft_strsub(s, 0, tab2d[i + 1] - s)))
		{
			ft_free_2d_tab(tab2d);
			return (NULL);
		}
		s = tab2d[i + 1];
		i++;
	}
	tab2d[i] = 0;
	return (tab2d);
}
