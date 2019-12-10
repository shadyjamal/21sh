/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjamal <cjamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 11:05:32 by cjamal            #+#    #+#             */
/*   Updated: 2019/12/06 17:10:23 by cjamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include "../libft/libft.h"
# define PID "12452"
# define SYMBOL "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ "

pid_t			g_childprc_pid;

enum
{
	ERR_CMDNTFD,
	ERR_MNARGS,
	ERR_PRMDND,
	ERR_FWARGS,
	ERR_FSTLTR,
	ERR_ALFA,
	ERR_NOT_DIR,
	ERR_NTFOUND,
	ERR_NOTSET,
	ERR_UNMATCHED,
};

t_list			*ft_parsecmd(char *buffer, t_list **env);
void			ft_shellmain(char **cmd, t_list *env);
void			ft_echo(char **cmd);
void			ft_env(t_list **env, char **cmd);
void			ft_cd(char **cmd, t_list **env);
void			ft_setenv(char **cmd, t_list **env);
void			ft_unsetenv(char **cmd, t_list **env);
t_list			*tab_to_list(char **env);
char			**list_to_tab(t_list *env, int flag);
t_list			**ft_lstfind(t_list **lst, const char *needle, size_t size);
void			ft_lstonedel(t_list **to_del);
void			ft_lstmodifone(t_list *to_mod, char *value);
int				ft_strisalnum(char *str);
int				ft_lstdup(t_list **begin, t_list **env);
int				ft_is_link(char *path);
_Bool			is_dir(char *file_name);
void			ft_display_prompt(void);
void			ft_print_error(char *str, int er, char c);
void			freecontent(void *content, size_t contentsize);
void			freetab (char **tab);
int				ft_tabsize(char **tab);

#endif
