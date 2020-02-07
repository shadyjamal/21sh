/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 16:46:05 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/24 16:51:59 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge_cmd(t_cmd_holder *hold, char *str)
{
	char	*tmp;
	int		len;

	tmp = hold->buff;
	len = ft_strlen(hold->buff);
	if ((hold->buff = ft_strnjoin((char *[]){hold->buff, "\n", str}, 3)))
		hold->cmd = hold->buff + len;
	if (str)
		free(str);
	if (!hold->buff)
		hold->cmd = NULL;
	free(tmp);
}

char	*readline_sequel(char **buff, int *buff_len)
{
	char	*line;

	if ((line = ft_readline(">")))
	{
		if (!(*buff = ft_realloc(*buff, *buff_len + 1, ft_strlen(line) + 1)))
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}
