/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 18:42:23 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/28 13:15:31 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd)
{
	int i;

	i = 0;
	while (cmd[++i])
	{
		ft_putstr(cmd[i]);
		cmd[i] ? write(1, " ", 1) : 0;
	}
	write(1, "\n", 1);
}

void	ft_unsetenv(char **cmd, t_list **env)
{
	int		i;
	t_list	**del;

	i = 1;
	while (cmd[i])
	{
		if ((del = ft_lstfind(env, cmd[i], ft_strlen(cmd[i]) + 1)))
			ft_lstonedel(del);
		i++;
	}
	if (i == 1)
		return (ft_print_error(cmd[0], ERR_FWARGS, 0));
}
