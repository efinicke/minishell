/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_fix_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:18:23 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/02 15:09:17 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_whitespaces(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

static int	pass_whitespaces(int i, char *cmd_src)
{
	while (cmd_src && cmd_src[i] && is_whitespaces(cmd_src[i]))
		i++;
	return (i);
}

char	*fix_spaces(char *cmd_src, t_lx *datas)
{
	int		i;
	char	*cmd_dst;

	i = 0;
	cmd_dst = NULL;
	reinitialise_datas_struct(datas);
	i = pass_whitespaces(i, cmd_src);
	while (cmd_src && cmd_src[i])
	{
		if ((datas->dquotes_mode + datas->squotes_mode) == 0
			&& is_whitespaces(cmd_src[i]))
		{
			i = pass_whitespaces(i, cmd_src);
			if (cmd_src[i] != '\0')
				cmd_dst = str_c_join(cmd_dst, ' ');
			else
				break ;
		}
		check_quotes_mode(cmd_src[i], datas);
		cmd_dst = str_c_join(cmd_dst, cmd_src[i]);
		i++;
	}
	free(cmd_src);
	return (cmd_dst);
}
