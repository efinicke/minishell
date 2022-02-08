/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_fill_cmds_in_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:49:50 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/02 23:40:53 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_active_pipe_on_str(char *cmd_src, t_lx *datas)
{
	int		i;

	i = 0;
	reinitialise_datas_struct(datas);
	while (cmd_src && cmd_src[i])
	{
		check_quotes_mode(cmd_src[i], datas);
		if (datas->squotes_mode + datas->dquotes_mode == 0)
		{
			if (cmd_src[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

void	fill_cmds_datas_struct_with_cmd_line(char *cmd_line, t_lx *datas)
{
	int	i;

	i = 0;
	reinitialise_datas_struct(datas);
	if (!cmd_line)
		return ;
	if (!is_active_pipe_on_str(cmd_line, datas))
		datas->cmds = add_str_in_tab(cmd_line, datas->cmds);
	while (cmd_line && cmd_line[i])
	{
		check_quotes_mode(cmd_line[i], datas);
		if ((datas->squotes_mode + datas->dquotes_mode) == 0
			&& (cmd_line[i] == '|'))
		{
			cmd_line[i] = '\0';
			datas->cmds = add_str_in_tab(cmd_line, datas->cmds);
			cmd_line = &cmd_line[i + 1];
			fill_cmds_datas_struct_with_cmd_line(cmd_line, datas);
			break ;
		}
		i++;
	}
}
