/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_fill_argv_and_argc2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 01:08:45 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/06 19:24:56 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	return_str_tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	fill_argc(t_cmd *cmd_lst)
{
	cmd_lst->argc = return_str_tab_size(cmd_lst->argv);
}

void	fill_argv_and_argc(char *cmd, t_cmd *cmd_lst, t_lx *datas, char **envp)
{
	fill_argv(cmd, cmd_lst, datas, envp);
	fill_argc(cmd_lst);
}
