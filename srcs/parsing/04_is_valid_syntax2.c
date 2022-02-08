/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_is_valid_syntax2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:48:52 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/06 16:44:41 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_white_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

static int	is_redir_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	is_valid_syntax_2(char *cmd)
{
	int	i;

	i = str_len(cmd) - 1;
	if (cmd == NULL)
		return (1);
	while (i > 0 && cmd && cmd[i] && is_white_space(cmd[i]))
		i--;
	if (is_redir_char(cmd[i]) || cmd[0] == '|')
	{
		send_error("syntax error");
		g_return_code = 2;
		return (0);
	}
	return (1);
}
