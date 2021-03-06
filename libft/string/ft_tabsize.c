/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 22:02:30 by cjamal            #+#    #+#             */
/*   Updated: 2020/01/24 22:02:32 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tabsize(char **tab)
{
	int size;

	size = 0;
	if (tab)
	{
		while (tab[size])
			size++;
	}
	return (size);
}
