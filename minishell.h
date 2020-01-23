
#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>
#include <fcntl.h>
#include "readline/ft_readline.h"
#include "libft/includes/libft.h"
#undef tab
#define NO_BUILTIN -2
#define NO_LOGIC_SEP -3
#define C_TAB (char *[])
#define PID "12452"
#define PRINCIPALE_ENV_VAR "HOME", "PWD", "OLDPWD", "PATH"
#define CLOSED_FD 2147483647
#define SEPARATOR "&;<>|"
#define SEPARATOR_TR "\5\6\7\x08\x09";
#define PRINT_ERROR(s1, s2) ft_printf("%w21sh: %s: %s\n", 2, s1, s2)

#define FILE_NOTFOUND "no such file or directory"
#define NOT_DIR "Not a directory."
#define IS_DIR "Is a directory"
#define PERM_DENYD "permission denied."
#define NOT_SET "not set."
#define FEW_ARGS "Too few arguments."
#define MANY_ARGS "Too many arguments."
#define BEGIN_BY_LETTER "name must begin with a letter."
#define CONTAIN_ALPHANUM "Variable name must contain just alphanum chars."
#define CMD_NOT_FOUND "command not found"
#define UNMATCHED  "unmatched" 
#define BAD_FD "Bad file descriptor"
#define AMB_REDIR "ambiguous redirect"

pid_t g_child_prc_pid;
t_list **g_pwd;
int *g_prompt_error;
char prompt[260];

enum
{
	NO_REDIR,
	REDIR_OUT,
	REDIR_IN,
	APPEND_OUT,
	HEREDOC,
	DUPLIC_OUT,
	DUPLIC_IN,
};

typedef struct s_env_var
{
	t_list *home;
	t_list *pwd;
	t_list *oldpwd;
	t_list *path;
	int error;
} t_env_var;

typedef struct s_redirs
{
	int typeredir;
	char *word;
	int n;
	struct s_redirs *next;
} t_redirs;

typedef struct s_cmd_holder
{
	char ***tabsep;
	char ***taband_or;
	char ***tabpipe;
	char **tabcmd;
	t_redirs **tab_redir;
	t_list *env;
	t_list *lstcmd;
	t_list *logic;
	char *buff;
	char *cmd;
	int size_cmd;
	int size_sep;
	int fd_backup[3];
} t_cmd_holder;

/*
** bultins
*/
int ft_cd(char **cmd, t_env_var *var, char *path);
int ft_echo(char **cmd);
int ft_env(t_list **env, char **cmd, t_env_var *var);
int ft_setenv(char **cmd, t_list **env, t_env_var *var);
int ft_unsetenv(char **cmd, t_list **env);
int ft_display_env(t_list *env);

/*
** utils
*/
void ft_lstonedel(t_list **to_del);
void ft_lstmodifone(t_list *to_mod, char *value);
void ft_display_prompt(char *prt, int error);
t_list *tab_to_list(char **env);
char **list_to_tab(t_list *env, int flag);
int ft_ltrcount(char **cmd, char *ltr);
int ft_logiccount(char **cmd);
void ft_pipefd(int *fd, int pipecount);
void ft_closefd(int fdcount, int *fd);
pid_t fork_process(void);

/*
** Parsing
*/
char ***parse_or_and(char **cmd, int count, t_list **logic);
char ***parsesep(char **cmd, int sep_count, char *sep, int *size_sep);
t_list *ft_parsecmd(t_cmd_holder *hold, t_list **env, t_env_var *var);
char *ft_parse_arg(t_cmd_holder *hold, char **buff);

/*
** Execution
*/
int ft_exec_bin(char **cmd, t_env_var *var, t_list *env, _Bool fork);
void ft_execpipe(t_cmd_holder *hold, int pipecount, t_env_var *var, int *ret);
int ft_exec_builtin(t_cmd_holder *hold, t_env_var *var, int ind);
void ft_execsimple_cmd(t_cmd_holder *hold, t_env_var *var, int *ret);
int ft_mainexec(t_cmd_holder *hold, t_env_var *var);

/* redirections */
t_redirs **ft_alloc_tabredirs(t_list **lstcmd);
int ft_exec_redirections(t_redirs *tabredir);
t_redirs	*ft_create_redir(t_list *occur, char *idx_redir);

/*
** Free
*/
void ft_free(t_cmd_holder *hold);

// debug
void printmatrix(char **cmd);
void printlst(t_list *lst);
void printlstredirs(t_redirs **tabredir);

#endif
