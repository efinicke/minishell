/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   23_test_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 03:59:09 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/08 03:59:14 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_str_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s;", tab[i]);
		i++;
	}
}

void	display_int_tab(int *tab)
{
	int	i;

	i = 0;
	while (tab[i] != -1)
	{
		printf("%d;", tab[i]);
		i++;
	}
}

void	display_cmd_lst(t_cmd *cmd_lst)
{
	int	i;

	i = 0;
	while (cmd_lst != NULL)
	{
		printf("\n----------LIST %d----------\n", i);
		printf("FILES: ");
		display_str_tab(cmd_lst->file);
		printf("\nTYPES: ");
		display_int_tab(cmd_lst->type);
		printf("\nARGV : ");
		display_str_tab(cmd_lst->argv);
		printf("\nARGC : ");
		printf("%d\n", cmd_lst->argc);
		cmd_lst = cmd_lst->next;
		i++;
	}
}
