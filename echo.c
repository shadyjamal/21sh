/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 23:22:41 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/11/29 05:33:02 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		ft_putstr(cmd[i]);
		cmd[i] ? write(1, " ", 1) : 0;
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

int	ft_display_env(t_list *e)
{
	while (e)
	{
		if (e->content && e->content_size > 0)
			ft_printf("%s=%s\n", e->content,
										e->content + ft_strlen(e->content) + 1);
		e = e->next;
	}
	return (0);
}
