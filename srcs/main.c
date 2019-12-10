/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:13:19 by cjamal            #+#    #+#             */
/*   Updated: 2019/12/08 16:32:11 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_procces(int signal)
{
	(void)signal;
	if (g_childprc_pid == 0)
	{
		ft_putchar('\n');
		ft_display_prompt();
	}
}

void	dispatcher(char **cmd, t_list **env)
{
	if (!cmd[0])
		return ;
	else if (ft_strequ(cmd[0], "exit"))
	{
		freetab(cmd);
		ft_lstdel(env, &freecontent);
		exit(0);
	}
	else if (ft_strequ(cmd[0], "cd"))
		ft_cd(cmd, env);
	else if (ft_strequ(cmd[0], "echo"))
		ft_echo(cmd);
	else if (ft_strequ(cmd[0], "env"))
		ft_env(env, cmd);
	else if (ft_strequ(cmd[0], "setenv"))
		ft_setenv(cmd, env);
	else if (ft_strequ(cmd[0], "unsetenv"))
		ft_unsetenv(cmd, env);
	else
		ft_shellmain(cmd, *env);
}
int comma_count(char **cmd)
{
	int i;
	int sepcount;
	
	i = 0;
	sepcount = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], ";"))
			sepcount += 1;
		i++;
	}
	return (sepcount);
}

char	***parsesep(char **cmd, int sep_count)
{
	int i;
	int j;
	char ***tab;
	
	tab = (char***)malloc(sizeof(char**) * (sep_count + 2));
	i = 0;
	j = 0;
	tab[j++] = &cmd[i];
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], ";"))
		{
			cmd[i] = 0;
			tab[j] = &cmd[i + 1];
			j++;
		}
		i++;
	}
	tab[j] = 0;
	return (tab);
}

int		main(int ac, char *av[], char *environ[])
{
	char		*buffer;
	char		**cmd;
	t_list		*env;
	t_list		*lstcmd;
	char		***tabsep;
	int			i;

	(void)av[ac * 0];	
	buffer = NULL;
	env = tab_to_list(environ);
	signal(SIGINT, kill_procces);
	while (1)
	{
		ft_display_prompt();
		if (get_next_line(0, &buffer) > 0)
		{
			lstcmd = ft_parsecmd(buffer, &env);
			ft_strdel(&buffer);
			cmd = list_to_tab(lstcmd, 0);
			ft_lstdel(&lstcmd, &freecontent);
			tabsep = cmd ? parsesep(cmd, comma_count(cmd)) : NULL;
			i = -1;
			while (tabsep[++i])
			 	dispatcher(tabsep[i], &env);
			freetab(cmd);
		}
		ft_strdel(&buffer);
		g_childprc_pid = 0;
	}
	return (0);
}
