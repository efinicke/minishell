/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_fill_file_and_type2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 05:14:07 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/07 16:19:43 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_redir_char(char c)
{
	return (c == '>' || c == '<');
}

void	pass_and_count_redir(char *cmd, t_lx *datas)
{
	while (is_redir_char(cmd[datas->pos]))
	{
		datas->type++;
		cmd[datas->pos] = ' ';
		datas->pos++;
	}
	if (cmd[datas->pos] == 32)
		datas->pos++;
}

void	add_type(int type_code, t_cmd *cmd_lst, int file_type)
{
	if (file_type == infile_c)
	{
		if (type_code == 1)
			cmd_lst->type = add_int_in_tab(0, cmd_lst->type);
		else if (type_code == 2)
			cmd_lst->type = add_int_in_tab(1, cmd_lst->type);
	}
	else if (file_type == outfile_c)
	{
		if (type_code == 1)
			cmd_lst->type = add_int_in_tab(2, cmd_lst->type);
		else if (type_code == 2)
			cmd_lst->type = add_int_in_tab(3, cmd_lst->type);
	}
}

void	fill_file(char *file, t_lx *datas, t_cmd *cmd_lst, char **envp)
{
	if (!file)
		return ;
	file = replace_dollar_var_by_val(file, envp, datas);
	file = fix_spaces(file, datas);
	file = remove_quotes(file, datas);
	if (file == NULL)
	{
		file = (char *)malloc(sizeof(char) * 1);
		if (!(file))
			return ;
		file[0] = '\0';
	}
	cmd_lst->file = add_str_in_tab(file, cmd_lst->file);
	free(file);
	datas->type = 0;
}
