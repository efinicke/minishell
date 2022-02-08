/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_fill_argv_and_argc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 06:27:06 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/07 16:21:23 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_active_space_on_str(char *cmd, t_lx *datas)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if ((datas->dquotes_mode + datas->squotes_mode) == 0)
		{
			if (cmd[i] == ' ')
				return (1);
		}
		check_quotes_mode(cmd[i], datas);
		i++;
	}
	return (0);
}

static void	fill_argv_file(char *argv, t_cmd *cmd_lst, char **envp, t_lx *datas)
{
	argv = replace_dollar_var_by_val(argv, envp, datas);
	argv = fix_spaces(argv, datas);
	argv = remove_quotes(argv, datas);
	if (argv == NULL)
	{
		argv = (char *)malloc(sizeof(char) * 1);
		if (!(argv))
			return ;
		argv[0] = '\0';
	}
	if (datas->var == 0)
		cmd_lst->argv = add_str_in_tab(argv, cmd_lst->argv);
	if (argv)
		free(argv);
	datas->var = 0;
}

void	fill_argv2(char *cmd, t_cmd *cmd_lst, t_lx *datas, char **envp)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (cmd && cmd[i])
	{
		if ((datas->dquotes_mode + datas->squotes_mode) == 0)
		{
			if (cmd[i] == ' ')
			{
				cmd[i] = '\0';
				tmp = str_dup(cmd);
				fill_argv_file(tmp, cmd_lst, envp, datas);
				if (cmd[i + 1])
				{
					cmd = &cmd[i + 1];
					fill_argv(cmd, cmd_lst, datas, envp);
					break ;
				}
			}
		}
		check_quotes_mode(cmd[i], datas);
		i++;
	}
}

void	fill_argv(char *cmd, t_cmd *cmd_lst, t_lx *datas, char **envp)
{
	char	*tmp;

	tmp = NULL;
	reinitialise_datas_struct(datas);
	if (cmd == NULL)
		return ;
	if (!is_active_space_on_str(cmd, datas))
	{
		tmp = str_dup(cmd);
		fill_argv_file(tmp, cmd_lst, envp, datas);
		return ;
	}
	fill_argv2(cmd, cmd_lst, datas, envp);
}
