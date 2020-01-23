
#include "minishell.h"

t_list	*get_env_var(const char *key, t_env_var *var)
{
	if (ft_strequ(key, "HOME"))
		return (var->home);
	if (ft_strequ(key, "PATH"))
		return (var->path);
	if (ft_strequ(key, "PWD"))
		return (var->pwd);
	if (ft_strequ(key, "OLDPWD"))
		return (var->oldpwd);
	else
		return (NULL);
}

void	create_modify_env(t_list **env, char *key, char *val, t_env_var *var)
{
	t_list **ptr;
	t_list *ptr2;

	if (var && (ptr2 = get_env_var(key, var)))
	{
		val = ft_strnjoin((char *[]){key, "=", val}, 3);
		ft_lstmodifone(ptr2, val);
		ft_strreplace(val, '=', 0);
	}
	else if ((ptr = ft_lstfind(env, key, ft_strlen(key) + 1)))
	{
		val = ft_strnjoin((char *[]){key, "=", val}, 3);
		ft_lstmodifone(*ptr, val);
		ft_strreplace(val, '=', 0);
	}
	else
	{
		val = ft_strnjoin((char *[]){key, "=", val}, 3);
		ptr2 = ft_lstpushback(env, val, strlen(val) + 1);
		ft_strreplace(ptr2->content, '=', 0);
		free(val);
	}
}

int		ft_unsetenv(char **cmd, t_list **env)
{
	int		i;
	t_list	**del;

	i = 1;
	while (cmd[i])
	{
		if ((del = ft_lstfind(env, cmd[i], ft_strlen(cmd[i]) + 1)))
		{
			if (ft_str_in_arr(cmd[i], (char *[]){PRINCIPALE_ENV_VAR, 0}))
				ft_memdel(&(*del)->content);
			else
				ft_lstonedel(del);
		}
		i++;
	}
	if (i == 1)
		return (PRINT_ERROR(cmd[0], FEW_ARGS));
	return (0);
}

int		ft_setenv(char **cmd, t_list **env, t_env_var *var)
{
	if (cmd[1] && cmd[2] && cmd[3])
		return (PRINT_ERROR(cmd[0], MANY_ARGS));
	if (!cmd[1])
		return (ft_display_env(*env));
	if (!ft_isalpha(cmd[1][0]))
		return (PRINT_ERROR(cmd[0], BEGIN_BY_LETTER));
	if (!ft_str_match(cmd[1], ft_isalnum))
		return (PRINT_ERROR(cmd[0], CONTAIN_ALPHANUM));
	create_modify_env(env, cmd[1], (cmd[2] ? cmd[2] : ""), var);
	return (0);
}

int		ft_env(t_list **env, char **cmd, t_env_var *var)
{
	t_list	*dup;
	char	*val;
	int		i;

	if (!cmd[1] && env)
		return (ft_display_env(*env));
	dup = cmd[1] && ft_strequ(cmd[1], "-i") ? NULL : ft_lstdup(env);
	i = 1 + ft_strequ(cmd[1], "-i");
	while (cmd[i])
	{
		if ((val = ft_strchr(cmd[i], '=')) && ft_strreplace(cmd[i], '=', 0))
			create_modify_env(&dup, cmd[i], val + 1, NULL);
		else
		{
			i = ft_exec_bin(cmd + i, var, dup, 1);
			ft_lstdel(&dup);
			return (i);
		}
		i++;
	}
	if (!cmd[i])
		return (ft_display_env(dup));
	return (0);
}
