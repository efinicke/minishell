/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_is_valid_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 02:44:03 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/02 15:58:59 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ignore_quotes_switch(int q_switch)
{
	if (q_switch == 0)
		return (1);
	if (q_switch == 1)
		return (0);
	return (0);
}

void	check_quotes_mode(char c, t_lx *datas)
{
	if (c == '\"' && datas->squotes_mode == 0)
		datas->dquotes_mode = ignore_quotes_switch(datas->dquotes_mode);
	if (c == '\'' && datas->dquotes_mode == 0)
		datas->squotes_mode = ignore_quotes_switch(datas->squotes_mode);
}

int	is_valid_quotes(char *cmd_src, t_lx *datas)
{
	int	i;

	i = 0;
	reinitialise_datas_struct(datas);
	while (cmd_src && cmd_src[i])
	{
		check_quotes_mode(cmd_src[i], datas);
		if (datas->squotes_mode == 0 && cmd_src[i] == '\"')
			datas->dq++;
		if (datas->dquotes_mode == 0 && cmd_src[i] == '\'')
			datas->sq++;
		i++;
	}
	if (datas->sq % 2 || datas->dq % 2)
		return (0);
	return (1);
}
