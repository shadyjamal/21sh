/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_until_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:14:57 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/18 12:15:04 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_skip_unitl_char(char *str, const char *compare)
{
	while (str && *str && !ft_isinstr(*str, compare))
		str++;
	return (str);
}
