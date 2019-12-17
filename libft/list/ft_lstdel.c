/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:37:28 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/29 06:24:04 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst)
{
	t_list	*to_free;

	while (*alst)
	{
		to_free = *alst;
		*alst = (*alst)->next;
		free(to_free->content);
		free(to_free);
	}
	*alst = NULL;
}
