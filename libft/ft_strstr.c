/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 09:08:57 by cjamal            #+#    #+#             */
/*   Updated: 2019/04/09 13:57:28 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	if (!*to_find)
		return ((char*)str);
	if (!*str)
		return (NULL);
	else if (ft_strncmp(str, to_find, ft_strlen((char*)to_find)) == 0)
		return ((char*)str);
	else
		return (ft_strstr(str + 1, to_find));
}
