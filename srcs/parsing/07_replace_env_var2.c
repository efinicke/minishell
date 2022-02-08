/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_replace_env_var2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:16:48 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/07 15:50:26 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_targeted_char(char c)
{
	return (c == '\0' || c == '\"' || c == '\'' || c == '/'
		|| c == '$' || c == 32 || (c >= 9 && c <= 13));
}

static int	is_targeted_char2(char c)
{
	return (c == '\0' || c == '$'
		|| c == 32 || (c >= 9 && c <= 13));
}

static char	*return_end(int i, char *cmd_src, char *env_val, t_lx *datas)
{
	if (cmd_src[i] == '\'' || cmd_src[i] == '\"')
	{
		while (cmd_src && !is_targeted_char2(cmd_src[i]))
		{
			env_val = str_c_join(env_val, cmd_src[i]);
			i++;
		}
	}
	datas->pos = i;
	return (env_val);
}

char	*put_env_val(char *cmd_dst, char *cmd_src, t_lx *datas, char **envp)
{
	int		i;
	char	*env_var;
	char	*env_val;

	env_var = NULL;
	env_val = NULL;
	i = datas->pos + 1;
	while (cmd_src && !is_targeted_char(cmd_src[i]))
	{
		env_var = str_c_join(env_var, cmd_src[i]);
		i++;
	}
	if (env_var)
		env_val = str_dup(get_env(env_var, envp));
	free(env_var);
	env_val = return_end(i, cmd_src, env_val, datas);
	if (env_val == NULL)
		datas->var = 1;
	cmd_dst = strjoin_free(cmd_dst, env_val);
	return (cmd_dst);
}

void	put_val(char *cmd_src, char **cmd_dst, char **envp, t_lx *datas)
{
	int	j;

	j = 1;
	while (j == 1)
	{
		if (cmd_src[datas->pos + 1] == '$' || cmd_src[datas->pos + 1] == ' '
			|| cmd_src[datas->pos + 1] == '\0')
			break ;
		if (cmd_src[datas->pos + 1] == '?')
		{
			*cmd_dst = put_return_val(*cmd_dst);
			datas->pos += 2;
		}
		else
			*cmd_dst = put_env_val(*cmd_dst, cmd_src, datas, envp);
		if (cmd_src[datas->pos] == '$')
			j = 1;
		else
			j = 0;
	}
}
