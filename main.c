
#include "minishell.h"
#include <readline/readline.h>

int		ft_tabsize(char **tab)
{
	int size;

	size = 0;
	while (tab[size])
		size++;
	return (size);
}

void	kill_procces(int signal)
{
	(void)signal;
	ft_putstr_fd("\n",0);
	g_read_interrput = 1;
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
	t_list			*lstcmd;
	t_env_var		var;
	t_cmd_holder	*hold;

	(void)av[ac * 0];
	hold = (t_cmd_holder *)ft_memalloc(sizeof(t_cmd_holder));
	ft_bzero(prompt, 260);
	init(environ, &hold->env, &var);
	while (1)
	{
		g_read_interrput = 0;
		ft_display_prompt(var.pwd->content, var.error);
		if ((hold->buff = ft_readline(prompt)))
		{
			lstcmd = ft_parsecmd(hold, &hold->env, &var);
			hold->tab_redir = ft_alloc_tabredirs(&lstcmd);
			hold->tabcmd = list_to_tab(lstcmd, 0);
			hold->size_cmd = ft_tabsize(hold->tabcmd);
			ft_strdel(&hold->buff);
			ft_lstdel(&lstcmd);
			var.error = ft_mainexec(hold, &var);
			ft_free(hold);
		}
		// else if (*hold->buff == '\4')
		// {
		// 	ft_strdel(&hold->buff);
		// 	exit(0);
		// }
		ft_strdel(&hold->buff);
		g_child_prc_pid = 0;
	}
	return (0);
}
