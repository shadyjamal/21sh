/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 01:00:01 by cjamal            #+#    #+#             */
/*   Updated: 2020/02/07 16:13:58 by cjamal           ###   ########.fr       */
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
		cmd[i + 1] ? write(1, " ", 1) : 0;
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
