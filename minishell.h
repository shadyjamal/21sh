/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:32:29 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/17 17:56:30 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include "libft/includes/libft.h"

# define C_TAB (char *[])
# define PID "12452"
# define PRINCIPALE_ENV_VAR "HOME", "PWD", "OLDPWD", "PATH"
# define SYMBOL "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"

# define PRINT_ERROR(s1, s2) ft_printf("minishell: %s: %s\n", s1, s2)

# define FILE_NOTFOUND "no such file or directory"
# define NOT_DIR "Not a directory."
# define PERM_DENYD "permission denied."
# define NOT_SET "not set."
# define FEW_ARGS "Too few arguments."
# define MANY_ARGS "Too many arguments."
# define BEGIN_BY_LETTER "name must begin with a letter."
# define CONTAIN_ALPHANUM "Variable name must contain just alphanum chars."
# define CMD_NOT_FOUND "command not found"
# define UNMATCHED "unmatched"

pid_t			g_child_prc_pid;
t_list			**g_pwd;
int				*g_prompt_error;

typedef struct	s_env_var
{
	t_list		*home;
	t_list		*pwd;
	t_list		*oldpwd;
	t_list		*path;
	int			error;
}				t_env_var;

t_list			*ft_parsecmd(char *buffer, t_list **env, t_env_var *var);

char			*ft_shellmain(char **cmd, t_env_var *var);

/*
** bultins
*/
int				ft_cd(char **cmd, t_env_var *var, char *path);
int				ft_echo(char **cmd);
int				ft_env(t_list **env, char **cmd, t_env_var *var);
int				ft_setenv(char **cmd, t_list **env, t_env_var *var);
int				ft_unsetenv(char **cmd, t_list **env);
int				ft_display_env(t_list *env);

/*
** utils
*/
void			ft_lstonedel(t_list **to_del);
void			ft_lstmodifone(t_list *to_mod, char *value);
void			ft_display_prompt(char *prt, int error);
t_list			*tab_to_list(char **env);
char			**list_to_tab(t_list *env, int flag);

// 21sh
char			***parsesep(char **cmd, int sep_count, char *sep);
int				ft_ltrcount(char **cmd, char *ltr);
void			ft_execpipe(char ***cmd, int pipecount, t_list *env, t_env_var *var);
int				dispatch(char **cmd, t_list **env, t_env_var *var, char **cmdpath);

// debug
void printmatrix(char **cmd);

#endif
