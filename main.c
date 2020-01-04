/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 00:14:15 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/04 17:29:54 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void kill_procces(int signal)
{
	(void)signal;
	if (g_child_prc_pid == 0)
	{
		ft_putstr("\n");
		ft_display_prompt((*g_pwd)->content, *g_prompt_error);
	}
}

void env_var_protection(t_env_var *var, t_list **env)
{
	if (!var->home || !var->path || !var->pwd || !var->oldpwd)
	{
		ft_lstdel(env);
		exit(0);
	}
}

void init(char *environ[], t_list **env, t_env_var *var)
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

int dispatch(char **cmd, t_list **env, t_env_var *var, char **cmdpath)
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
	if ((*cmdpath = ft_shellmain(cmd, var)) != NULL)
		return (0);
	return (1);
}

void ft_mainexec(t_cmd_holder *holder, t_env_var *var)
{
	int i;
	int pipecount;
	
	i = 0;
	while (holder->tabsep[i])
	{
		pipecount = ft_ltrcount(holder->tabsep[i], "|");
		holder->tabpipe = parsesep(holder->tabsep[i], pipecount, "|");
		if (holder->tabpipe[0] && !holder->tabpipe[1])
		{
			ft_execsimple_cmd(holder, var);
			holder->tab_redir++;
		}
		else 
		{
			ft_execpipe(holder, pipecount, var);
			holder->tab_redir += pipecount + 1;
		}
		i++;
	}
}

int main(int ac, char *av[], char *environ[])
{
	char *buffer;
	char **cmd;
	t_list *lstcmd;
	t_env_var var;
	t_cmd_holder *hold;
	
	(void)av[ac * 0];
	buffer = NULL;
	hold = (t_cmd_holder *)malloc(sizeof(t_cmd_holder));
	init(environ, &hold->env, &var);
	while (1)
	{
		ft_display_prompt(var.pwd->content, var.error);
		if (get_next_line(0, &buffer) > 0)
		{
			lstcmd = ft_parsecmd(buffer, &hold->env, &var);\
			// Parse redirst_redirs
			hold->tab_redir = ft_alloc_tabredirs(&lstcmd);
			//printlstredirs(hold->tab_redir);
			cmd = list_to_tab(lstcmd, 0);
			ft_strdel(&buffer);
			ft_lstdel(&lstcmd);
			hold->tabsep = parsesep(cmd, ft_ltrcount(cmd, ";"), ";");
			//parse && ||
			ft_mainexec(hold, &var);
			ft_free_2d_tab(cmd);
		}
		ft_strdel(&buffer);
		g_child_prc_pid = 0;
	}
	return (0);
}
