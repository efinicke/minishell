/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_utils_linked_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:19:35 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/07 23:45:01 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_cmd_lst_datas(t_cmd *cmd_lst)
{
	cmd_lst->path = NULL;
	cmd_lst->file = (char **)malloc(sizeof(char *));
	if (!cmd_lst->file)
		return ;
	cmd_lst->file[0] = NULL;
	cmd_lst->type = (int *)malloc(sizeof(int));
	if (!cmd_lst->type)
		return ;
	cmd_lst->type[0] = -1;
	cmd_lst->infile = -1;
	cmd_lst->outfile = -1;
	cmd_lst->argc = 0;
	cmd_lst->argv = (char **)malloc(sizeof(char *));
	if (!cmd_lst->argv)
		return ;
	cmd_lst->argv[0] = NULL;
	cmd_lst->next = NULL;
}

t_cmd	*create_and_init_first_cmd_lst(void)
{
	t_cmd	*cmd_lst;

	cmd_lst = malloc(sizeof(t_cmd));
	if (!cmd_lst)
		return (NULL);
	else
		init_cmd_lst_datas(cmd_lst);
	return (cmd_lst);
}

t_cmd	*create_and_init_next_cmd_lst(t_cmd *last_cmd_lst)
{
	t_cmd	*next_cmd_lst;

	next_cmd_lst = malloc(sizeof(t_cmd));
	if (!next_cmd_lst)
		return (NULL);
	else
	{
		init_cmd_lst_datas(next_cmd_lst);
		last_cmd_lst->next = next_cmd_lst;
	}
	return (next_cmd_lst);
}
