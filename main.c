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

int		main(int ac, char *av[], char *environ[])
{
	char			*buffer;
	t_list			*lstcmd;
	t_env_var		var;
	t_cmd_holder	*hold;

	(void)av[ac * 0];
	buffer = NULL;
	hold = (t_cmd_holder *)ft_memalloc(sizeof(t_cmd_holder));
	init(environ, &hold->env, &var);
	while (1)
	{
		//ft_display_prompt(var.pwd->content, var.error);
		if ((buffer = readline("$> ")))
		{
			lstcmd = ft_parsecmd(buffer, &hold->env, &var);
			hold->tab_redir = ft_alloc_tabredirs(&lstcmd);
			hold->cmd = list_to_tab(lstcmd, 0);
			ft_strdel(&buffer);
			ft_lstdel(&lstcmd);
			var.error = ft_mainexec(hold, &var);
			ft_free(hold);
		}
		ft_strdel(&buffer);
		g_child_prc_pid = 0;
	}
	return (0);
}
