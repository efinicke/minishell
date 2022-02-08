/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_replace_env_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:16:48 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/08 00:34:06 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static unsigned int	ft_get_env_len(const char *env)
{
	unsigned int	i;

	if (!(env))
		return (0);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

char	*get_env(char *name, char **envp)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (envp[i] && (str_n_cmp(envp[i], name, str_len(name)) != 0 \
	|| (ft_strlen(name)) != ft_get_env_len(envp[i])))
		i++;
	if (!(envp[i]))
		return (NULL);
	j = 0;
	while (envp[i][j] != '=')
		j++;
	j++;
	return (envp[i] + j);
}

char	*put_return_val(char *cmd_dst)
{
	int		ret_val;
	char	*add_ret;

	ret_val = g_return_code;
	add_ret = ft_itoa(ret_val);
	cmd_dst = strjoin_free(cmd_dst, add_ret);
	return (cmd_dst);
}

char	*replace_dollar_var_by_val(char *cmd_src, char **envp, t_lx *datas)
{
	char	*cmd_dst;

	cmd_dst = NULL;
	reinitialise_datas_struct(datas);
	while (cmd_src && cmd_src[datas->pos])
	{
		check_quotes_mode(cmd_src[datas->pos], datas);
		if (cmd_src[datas->pos] == '$' && datas->squotes_mode == 0
			&& !(cmd_src[datas->pos + 1] == '\"' && datas->dquotes_mode == 1))
		{
			put_val(cmd_src, &cmd_dst, envp, datas);
			if (cmd_src[datas->pos] == '\0')
				break ;
		}
		cmd_dst = str_c_join(cmd_dst, cmd_src[datas->pos]);
		datas->pos++;
	}
	free(cmd_src);
	return (cmd_dst);
}
