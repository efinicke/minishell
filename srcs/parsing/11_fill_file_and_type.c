/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_fill_file_and_type.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 01:58:08 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/06 19:46:33 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	outfile_char(char c)
{
	return (c == '>');
}

static int	infile_char(char c)
{
	return (c == '<');
}

static int	is_redir_char(char c)
{
	return (c == '>' || c == '<');
}

char	*fill_file_and_type(char *cmd, t_cmd *cmd_lst, t_lx *datas, char **envp)
{
	char	*file;

	file = NULL;
	reinitialise_datas_struct(datas);
	while (cmd && cmd[datas->pos])
	{
		if ((datas->dquotes_mode + datas->squotes_mode) == 0
			&& is_redir_char(cmd[datas->pos]))
		{
			if (infile_char(cmd[datas->pos]))
				file = return_file(cmd, infile_c, datas, cmd_lst);
			else if (outfile_char(cmd[datas->pos]))
				file = return_file(cmd, outfile_c, datas, cmd_lst);
		}
		fill_file(file, datas, cmd_lst, envp);
		file = NULL;
		if (cmd[datas->pos] == '\0')
			break ;
		check_quotes_mode(cmd[datas->pos], datas);
		datas->pos++;
	}
	cmd = fix_spaces(cmd, datas);
	return (cmd);
}

char	*return_file(char *cmd, int file_type, t_lx *datas, t_cmd *cmd_lst)
{
	char	*file;

	file = NULL;
	pass_and_count_redir(cmd, datas);
	add_type(datas->type, cmd_lst, file_type);
	while (cmd && cmd[datas->pos])
	{
		if ((datas->dquotes_mode + datas->squotes_mode) == 0)
		{
			if (cmd[datas->pos] == ' ')
				break ;
			if (is_redir_char(cmd[datas->pos]))
			{
				datas->pos--;
				break ;
			}
		}
		check_quotes_mode(cmd[datas->pos], datas);
		file = str_c_join(file, cmd[datas->pos]);
		cmd[datas->pos] = ' ';
		datas->pos++;
	}
	return (file);
}
