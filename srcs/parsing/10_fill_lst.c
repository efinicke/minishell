/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_fill_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:40:07 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/06 19:42:27 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*fill_lst(t_lx *datas, char **envp)
{
	t_cmd	*first_cmd_lst;
	t_cmd	*cmd_lst;
	char	*cmd;
	int		i;

	first_cmd_lst = create_and_init_first_cmd_lst();
	cmd_lst = first_cmd_lst;
	cmd = NULL;
	i = 0;
	while (datas->cmds[i])
	{
		cmd = str_dup(datas->cmds[i]);
		cmd = fix_spaces(cmd, datas);
		cmd = put_tilde_var(cmd, datas);
		cmd = fill_file_and_type(cmd, cmd_lst, datas, envp);
		fill_argv_and_argc(cmd, cmd_lst, datas, envp);
		free(cmd);
		if (datas->cmds[i + 1])
			cmd_lst = create_and_init_next_cmd_lst(cmd_lst);
		i++;
	}
	return (first_cmd_lst);
}
