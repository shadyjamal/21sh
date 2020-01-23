/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:40:02 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/04 22:52:55 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(void *str, size_t size, size_t new_size)
{
	void	*res;

	res = ft_memalloc(new_size + size);
	ft_memcpy(res, str, size);
	free(str);
	return (res);
}
