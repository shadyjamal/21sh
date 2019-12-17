/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:14:15 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/17 17:58:00 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_procces(int signal)
{
	(void)signal;
	if (g_child_prc_pid == 0)
	{
		ft_putstr("\n");
		ft_display_prompt((*g_pwd)->content, *g_prompt_error);
	}
}

void	env_var_protection(t_env_var *var, t_list **env)
{
	if (!var->home || !var->path || !var->pwd || !var->oldpwd)
	{
		ft_lstdel(env);
		exit(0);
	}
}

void	init(char *environ[], t_list **env, t_env_var *var)
{
	t_list **ptr;

	g_pwd = &var->pwd;
	var->error = 0;
	g_prompt_error = &var->error;
	*env = tab_to_list(environ);
	signal(SIGINT, kill_procces);
	if ((ptr = ft_lstfind(env, "HOME", 5)))
		var->home = *ptr;
	else if ((var->home = ft_memalloc(sizeof(t_list))))
		ft_lstadd(env, var->home);
	if ((ptr = ft_lstfind(env, "PWD", 4)))
		var->pwd = *ptr;
	else if ((var->pwd = ft_memalloc(sizeof(t_list))))
		ft_lstadd(env, var->pwd);
	if ((ptr = ft_lstfind(env, "PATH", 5)))
		var->path = *ptr;
	else if ((var->path = ft_memalloc(sizeof(t_list))))
		ft_lstadd(env, var->path);
	if ((ptr = ft_lstfind(env, "OLDPWD", 7)))
		var->oldpwd = *ptr;
	else if ((var->oldpwd = ft_memalloc(sizeof(t_list))))
		ft_lstadd(env, var->oldpwd);
	env_var_protection(var, env);
}

int		dispatch(char **cmd, t_list **env, t_env_var *var, char **cmdpath)
{
	if (!cmd[0])
		return (-1);
	else if (ft_strequ(cmd[0], "exit"))
	{
		ft_free_2d_tab(cmd);
		ft_lstdel(env);
		exit(0);
	}
	if (ft_strequ(cmd[0], "cd"))
		return (ft_cd(cmd, var, NULL));
	if (ft_strequ(cmd[0], "echo"))
		return (ft_echo(cmd));
	if (ft_strequ(cmd[0], "env"))
		return (ft_env(env, cmd, var));
	if (ft_strequ(cmd[0], "setenv"))
		return (ft_setenv(cmd, env, var));
	if (ft_strequ(cmd[0], "unsetenv"))
		return (ft_unsetenv(cmd, env));
	if ((*cmdpath = ft_shellmain(cmd, var)))
		return (0);
	return (1);
}

void ft_mainexec(char ***tabsep, t_list *env, t_env_var *var)
{
	int	i;
	int pipecount;
	char ***tabpipe;

	i = 0;
	while (tabsep[i])
	{
		pipecount = ft_ltrcount(tabsep[i], "|");
		tabpipe = parsesep(tabsep[i], pipecount, "|");
		ft_execpipe(tabpipe, pipecount, env, var);
		i++;
	}
}

int		main(int ac, char *av[], char *environ[])
{
	char		*buffer;
	char		**cmd;
	t_list		*env;
	t_list		*lstcmd;
	char		***tabsep;
	t_env_var	var;

	(void)av[ac * 0];
	buffer = NULL;
	init(environ, &env, &var);
	while (1)
	{
		ft_display_prompt(var.pwd->content, var.error);
		if (get_next_line(0, &buffer) > 0)
		{
			lstcmd = ft_parsecmd(buffer, &env, &var);
			cmd = list_to_tab(lstcmd, 0);
			ft_strdel(&buffer);
			ft_lstdel(&lstcmd);
			tabsep = parsesep(cmd, ft_ltrcount(cmd, ";"), ";");
			ft_mainexec(tabsep, env, &var);
			ft_free_2d_tab(cmd);
		}
		ft_strdel(&buffer);
		g_child_prc_pid = 0;
	}
	return (0);
}
