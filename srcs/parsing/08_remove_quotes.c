/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:49:33 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/07 16:11:32 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_quotes(char *cmd_src, t_lx *datas)
{
	int		i;
	char	*cmd_dst;

	i = -1;
	cmd_dst = NULL;
	reinitialise_datas_struct(datas);
	while (cmd_src && cmd_src[++i])
	{
		check_quotes_mode(cmd_src[i], datas);
		if (cmd_src[i] && datas->squotes_mode == 0 && cmd_src[i] == '\"')
			continue ;
		else if (cmd_src[i] && datas->dquotes_mode == 0 && cmd_src[i] == '\'')
			continue ;
		if (cmd_src[i] != '\0')
			cmd_dst = str_c_join(cmd_dst, cmd_src[i]);
	}
	if (cmd_src)
		free(cmd_src);
	return (cmd_dst);
}
