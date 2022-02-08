/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_is_valid_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:18:35 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/02 18:09:56 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_sq_or_dq(char c)
{
	return (c == '\"' || c == '\'');
}

static int	is_bad_syntax(const char *cmd, int i, const char *test)
{
	int		len;
	int		j;
	char	*extract;

	j = 0;
	len = str_len(test);
	extract = malloc(sizeof(cmd) * len);
	if (!extract)
		return (0);
	if (str_len(&cmd[i]) < str_len(test))
	{
		free(extract);
		return (0);
	}
	while (j < len)
		extract[j++] = cmd[i++];
	extract[j] = '\0';
	if (str_cmp(extract, test) == 0)
	{
		free(extract);
		return (1);
	}
	free(extract);
	return (0);
}

static int	is_valid_stx(const char *stx_err_cases[],
	int i, char *cmd, t_lx *datas)
{
	while (cmd && cmd[i])
	{
		check_quotes_mode(cmd[i], datas);
		if ((datas->squotes_mode + datas->dquotes_mode) == 0
			&& !is_sq_or_dq(cmd[i]))
		{
			datas->pos = 0;
			while (stx_err_cases[datas->pos] != NULL)
			{
				if (is_bad_syntax(cmd, i, stx_err_cases[datas->pos]))
				{
					send_error("syntax error");
					g_return_code = 2;
					reinitialise_datas_struct(datas);
					return (0);
				}
				datas->pos++;
			}
		}
		i++;
	}
	return (1);
}

int	is_valid_syntax_1(char *cmd, t_lx *datas)
{
	int			i;
	const char	*stx_err_cases[] = {"> >", "< <", ">> >", "> >>", \
					"<< <", "<|", "< |", "<< |", "<<|", \
					">|", "> |", ">> |", ">>|", "< <<", \
					"| |", ";", ">>>", "<<<", "> <", "><", \
					"<>", "< >", "||", "| |", NULL};

	i = 0;
	reinitialise_datas_struct(datas);
	if (is_valid_stx(stx_err_cases, i, cmd, datas))
		return (1);
	return (0);
}
