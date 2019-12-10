/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:34:53 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/29 17:11:01 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	unsigned	int	ft_line_length(char *t)
{
	return (ft_strrchr(t, '\n') ? ft_strchr(t, '\n') - t : ft_strlen(t));
}

static	char			*ft_line_rest(char *tab)
{
	if (ft_strchr(tab, '\n'))
		return (ft_strcpy(tab, ft_strchr(tab, '\n') + 1));
	if (ft_line_length(tab) > 0)
		return (ft_strcpy(tab, ft_strchr(tab, '\0')));
	return (NULL);
}

int						get_next_line(int const fd, char **line)
{
	char		*tmp;
	char		*buff;
	static char	*tab[4867];
	int			r;

	buff = ft_strnew(BUFF_SIZE);
	if (fd < 0 || BUFF_SIZE < 1 || !line || read(fd, buff, 0) < 0)
		return (-1);
	if (!(tab[fd]) && !(tab[fd] = ft_strnew(0)))
		return (-1);
	while (!(ft_strchr(tab[fd], '\n')) && (r = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[r] = '\0';
		tmp = tab[fd];
		tab[fd] = ft_strjoin(tmp, buff);
		free(tmp);
	}
	*line = ft_strsub(tab[fd], 0, ft_line_length(tab[fd]));
	free(buff);
	return (ft_line_rest(tab[fd]) ? 1 : 0);
}
