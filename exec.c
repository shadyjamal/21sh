
#include "minishell.h"

int		cmd_access(char *cmd)
{
	if (cmd && !ft_is_dir(cmd) && !access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (0);
		else
			return (2);
	}
	return (1);
}

char	*find(char *cmd, t_env_var *var)
{
	char	*path;
	int		ret;
	int		permdeny;
	char	**paths;
	int		i;

	permdeny = 0;
	i = 0;
	paths = ft_strsplit(var->path->content ? var->path->content + 5 : "", ":");
	while (paths && paths[i])
	{
		path = ft_strnjoin((char *[]){paths[i], "/", cmd}, 3);
		if (!(ret = cmd_access(path)))
		{
			ft_free_2d_tab(paths);
			return (path);
		}
		i++;
		ret == 2 ? permdeny = ret : 0;
		free(path);
	}
	ft_free_2d_tab(paths);
	PRINT_ERROR(cmd, permdeny ? PERM_DENYD : CMD_NOT_FOUND);
	return (NULL);
}

char	*ft_find_bin(char **cmd, t_env_var *var)
{
	char	*cmd_path;
	int		ret;

	if (ft_strchr(cmd[0], '/'))
	{
		if ((ret = cmd_access(cmd[0])))
		{
			PRINT_ERROR(cmd[0], CMD_NOT_FOUND);
			return (NULL);
		}
		cmd_path = ft_strdup(cmd[0]);
	}
	else
		cmd_path = find(cmd[0], var);
	return (cmd_path);
}

int		ft_exec_builtin(t_cmd_holder *hold, t_env_var *var, int ind)
{
	if (!hold->tabpipe[ind][0])
		return (-1);
	else if (ft_strequ(hold->tabpipe[ind][0], "exit"))
		exit(0);
	if (ft_strequ(hold->tabpipe[ind][0], "cd"))
		return (ft_cd(hold->tabpipe[ind], var, NULL));
	if (ft_strequ(hold->tabpipe[ind][0], "echo"))
		return (ft_echo(hold->tabpipe[ind]));
	if (ft_strequ(hold->tabpipe[ind][0], "env"))
		return (ft_env(&hold->env, hold->tabpipe[ind], var));
	if (ft_strequ(hold->tabpipe[ind][0], "setenv"))
		return (ft_setenv(hold->tabpipe[ind], &hold->env, var));
	if (ft_strequ(hold->tabpipe[ind][0], "unsetenv"))
		return (ft_unsetenv(hold->tabpipe[ind], &hold->env));
	return (NO_BUILTIN);
}

int		ft_exec_bin(char **cmd, t_env_var *var, t_list *env, _Bool fork)
{
	char	*cmdpath;
	pid_t	process;
	char	**tab_env;
	int		ret;

	ret = -1;
	process = -1;
	tab_env = list_to_tab(env, 1);
	cmdpath = ft_find_bin(cmd, var);
	if (cmdpath)
	{
		if ((process = (fork ? fork_process() : -1)) == 0 || !fork)
		{
			if (execve(cmdpath, cmd, tab_env) == -1)
				exit(EXIT_FAILURE);
		}
		else if (process > 0)
			wait(&ret);
	}
	ft_free_2d_tab(tab_env);
	free(cmdpath);
	return (ret);
}
