/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:55:45 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/06 13:33:20 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

unsigned int	get_cmd_list_size(t_cmd *cmd)
{
	unsigned int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}
