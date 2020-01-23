
#include "minishell.h"

int	ft_exec_cmd(t_cmd_holder *hold, char **cmd, t_env_var *var, int pipecount)
{
	int ret;

	ret = 0;
	hold->tabpipe = parsesep(cmd, pipecount, "|", 0);
	if (!pipecount)
		ft_execsimple_cmd(hold, var, &ret);
	else
		ft_execpipe(hold, pipecount, var, &ret);
	free(hold->tabpipe);
	return (ret);
}

int	ft_exec_or_and(t_cmd_holder *hold, t_env_var *var, int count)
{
	int		i;
	int		ret;
	int		pipecount;
	t_list	*and_or;

	and_or = hold->logic;
	ret = 0;
	i = 0;
	while (i < count + 1)
	{
		pipecount = ft_ltrcount(hold->taband_or[i], "|");
		if (!i || (!ret && ft_strequ(and_or->content, "&&")) ||
			(ret && ft_strequ(and_or->content, "||")))
			ret = ft_exec_cmd(hold, hold->taband_or[i], var, pipecount);
		i ? and_or = and_or->next : 0;
		hold->tab_redir += pipecount + 1;
		i++;
	}
	ft_lstdel(&hold->logic);
	free(hold->taband_or);
	return (ret);
}

int	ft_handle_or_and(t_cmd_holder *hold, t_env_var *var, int index)
{
	int count;

	count = ft_logiccount(hold->tabsep[index]);
	hold->taband_or = parse_or_and(hold->tabsep[index], count, &hold->logic);
	if (hold->taband_or)
		return (ft_exec_or_and(hold, var, count));
	else
		return (NO_LOGIC_SEP);
}

int	ft_mainexec(t_cmd_holder *hold, t_env_var *var)
{
	int			i;
	int			ret;
	int			pipecount;
	int			sepcount;
	t_redirs	**tmp;

	i = -1;
	ret = 1;
	tmp = hold->tab_redir;
	hold->size_sep = 0;
	sepcount = ft_ltrcount(hold->tabcmd, ";");
	hold->tabsep = parsesep(hold->tabcmd, sepcount, ";", &hold->size_sep);
	while (++i < hold->size_sep)
	{
		ret = ft_handle_or_and(hold, var, i);
		if (ret == NO_LOGIC_SEP)
		{
			pipecount = ft_ltrcount(hold->tabsep[i], "|");
			ret = ft_exec_cmd(hold, hold->tabsep[i], var, pipecount);
			hold->tab_redir += pipecount + 1;
		}
	}
	hold->tab_redir = tmp;
	return (ret);
}
