#include "minishell.h"

char	*ft_strjoin_free(char const *s1, char const *s2, int i)
{
	char *str;

	str = ft_strjoin(s1, s2);
	if (i == 1)
		ft_strdel((char **)&s1);
	if (i == 2)
		ft_strdel((char **)&s2);
	if (i == 3)
	{
		ft_strdel((char **)&s1);
		ft_strdel((char **)&s2);
	}
	return (str);
}

void ft_redirect_out(char *fdout, _Bool append)
{
	int out;

	out = 1;
	if (fdout)
	{
		if (!append)
		{
			if ((out = open(fdout, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) < 0)
				return ; // error
		}
		else
		{
		     if ((out = open(fdout, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) < 0)
				return ;
		}
		dup2(out, 1); // replace standard output with output file
		close(out);
	}
}

void ft_redirect_in(char *fdin)
{
	int in;

	in = 0;
	if (fdin)
	{
		if ((in = open(fdin, O_RDONLY)) < 0)
			return ;
		dup2(in, 0); // replace standard input with input file
		close(in);
	}
}
// int    here_line(char **cmd)
// {
//     int     ret;
//     char    *entry;

//     entry = ft_strnew(4);
//     while ((ret = read(0, entry, 1)) > 0)
//     {
//         if (entry[0] == 10)
//             break ;
//         else if (ft_isprint(entry[0]))
//         {
//             entry[ret] = 0;
//             *cmd = ft_strjoin_free(*cmd, entry, 1);
//         }
//     }
//     ft_strdel(&entry);
//     return (ret);
// }

// int     prompt_heredoc(char *eof)
// {
//     char    *cmd;
//     char    *entry;
//     int i;
//     cmd = ft_strnew(0);
//     entry = ft_strnew(0);
//     while (ft_strcmp(cmd, eof) != 0)
//     {
//         if (i > 0)
//         {
//             entry = ft_strjoin_free(entry, ft_strjoin_free(cmd, "\n", 1), 3);
//             cmd = ft_strnew(0);
//         }
//         ft_putchar('>');
//         if (here_line(&cmd) == 0)
//         {
//             ft_putchar('\n');
//             ft_strjoin_free()
//         }
//         i++;
//     }
// }

void    ft_exec_redirections(t_redirs *tabredir)
{
    while (tabredir)
    {
        if (tabredir->typeredir == REDIR_OUT)
            ft_redirect_out(tabredir->word, 0);
        else if (tabredir->typeredir == APPEND_OUT)
            ft_redirect_out(tabredir->word, 1);
        else if (tabredir->typeredir == REDIR_IN)
            ft_redirect_in(tabredir->word);
        tabredir = tabredir->next;
    }
}