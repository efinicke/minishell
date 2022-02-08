/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_replace_tilde.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:49:08 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/07 16:02:31 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_targeted_char(char c)
{
	return (c == 32 || (c >= 9 && c <= 13) || c == '\0');
}

char	*put_tilde_var(char *cmd_src, t_lx *datas)
{
	int		i;
	char	*cmd_dst;

	i = 0;
	cmd_dst = NULL;
	reinitialise_datas_struct(datas);
	while (cmd_src && cmd_src[i])
	{
		check_quotes_mode(cmd_src[i], datas);
		if (cmd_src[i] == '~' && datas->squotes_mode + datas->dquotes_mode == 0
			&& is_targeted_char(cmd_src[i - 1])
			&& (is_targeted_char(cmd_src[i + 1]) || cmd_src[i + 1] == '/'))
		{
			i++;
			cmd_dst = strjoin_free(cmd_dst, str_dup("$HOME"));
			if (cmd_src[i] == '\0')
				break ;
		}
		cmd_dst = str_c_join(cmd_dst, cmd_src[i]);
		i++;
	}
	free(cmd_src);
	return (cmd_dst);
}
