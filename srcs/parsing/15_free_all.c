/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:50:57 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/02 23:44:28 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_str_tab(char **str_tab)
{
	unsigned int	i;

	if (!(str_tab))
		return ;
	i = 0;
	while (str_tab[i])
		free(str_tab[i++]);
	free(str_tab);
}

void	clear_datas_struct(t_lx *datas)
{
	clear_str_tab(datas->cmds);
	free(datas);
}

void	clear_cmd_lst(t_cmd *cmd_lst)
{
	t_cmd	*tmp;

	while (cmd_lst != NULL)
	{
		if (cmd_lst->path)
			free(cmd_lst->path);
		clear_str_tab(cmd_lst->argv);
		clear_str_tab(cmd_lst->file);
		free(cmd_lst->type);
		tmp = cmd_lst;
		cmd_lst = cmd_lst->next;
		free(tmp);
	}
}

void	clear_all(char *cmd, t_cmd *cmd_lst, t_lx *datas)
{
	if (datas)
		clear_datas_struct(datas);
	if (cmd_lst)
		clear_cmd_lst(cmd_lst);
	if (cmd)
		free(cmd);
}
