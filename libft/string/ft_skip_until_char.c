/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_until_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 21:19:58 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/25 04:21:19 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_skip_unitl_char(const char *str, const char *compare)
{
	while (str && *str && !ft_isinstr(*str, compare))
		str++;
	return (str);
}
