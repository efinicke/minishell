/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_utils_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:19:45 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/07 23:40:10 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lx	*init_datas_struct(t_lx *datas)
{
	datas = malloc(sizeof(t_lx));
	if (!datas)
		return (NULL);
	datas->cmds = (char **)malloc(sizeof(char *));
	if (!datas->cmds)
		return (NULL);
	datas->cmds[0] = NULL;
	datas->type = 0;
	datas->squotes_mode = 0;
	datas->dquotes_mode = 0;
	datas->sq = 0;
	datas->dq = 0;
	datas->var = 0;
	datas->pos = 0;
	return (datas);
}

void	reinitialise_datas_struct(t_lx	*datas)
{
	datas->type = 0;
	datas->squotes_mode = 0;
	datas->dquotes_mode = 0;
	datas->sq = 0;
	datas->dq = 0;
	datas->pos = 0;
}
