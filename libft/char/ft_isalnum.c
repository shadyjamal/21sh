/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:45:05 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/24 18:00:11 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((ft_isdigit(c) || ft_isalpha(c)) ? 1 : 0);
}

int	ft_isnalnum(int c)
{
	return (!(ft_isdigit(c) || ft_isalpha(c)));
}
