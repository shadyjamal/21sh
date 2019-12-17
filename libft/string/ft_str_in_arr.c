/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_in_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 03:44:05 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/29 14:27:51 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

_Bool	ft_str_in_arr(char *str, char **tab)
{
	if (str && tab)
	{
		while (*tab)
		{
			if (ft_strequ(str, *tab))
				return (1);
			tab++;
		}
	}
	return (0);
}
