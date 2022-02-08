/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_call_and_return_cmd_lst.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:48:23 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/06 20:06:36 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unclosed_quotes_error(void)
{
	send_error("unclosed quotes");
	g_return_code = 2;
}

static void	set_cmd_first(t_cmd *cmd)
{
	t_cmd	*first;

	first = cmd;
	while (cmd)
	{
		cmd->first = first;
		cmd = cmd->next;
	}
}

t_cmd	*parse_and_return_cmd_lst(char *line, char **envp)
{
	char	*cmd;
	t_lx	*datas;
	t_cmd	*cmd_lst;

	cmd = str_dup(line);
	datas = init_datas_struct(NULL);
	cmd_lst = NULL;
	if (is_valid_quotes(cmd, datas))
	{
		cmd = fix_spaces(cmd, datas);
		if (is_valid_syntax_1(cmd, datas) && is_valid_syntax_2(cmd))
		{
			fill_cmds_datas_struct_with_cmd_line(cmd, datas);
			cmd_lst = fill_lst(datas, envp);
		}
	}
	else
		unclosed_quotes_error();
	set_cmd_first(cmd_lst);
	if (datas)
		clear_datas_struct(datas);
	if (cmd)
		free(cmd);
	return (cmd_lst);
}
