/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_translate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 18:14:30 by cjamal            #+#    #+#             */
/*   Updated: 2019/11/25 19:25:48 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_translate(char *str, const char *from, const char *to)
{
	int i;

	if (!str || !from || !to)
		return ;
	while (*str)
	{
		i = 0;
		while (from[i])
		{
			if (*str == from[i])
			{
				*str = to[i];
				break ;
			}
			i++;
		}
		str++;
	}
}
