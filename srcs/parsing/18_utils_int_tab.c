/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_utils_int_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:20:08 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/02 23:45:09 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*add_int_in_tab(const int value, int *old_type)
{
	int				*new_type;
	unsigned int	i;
	unsigned int	size;

	size = 0;
	while (old_type[size] != -1)
		size++;
	new_type = malloc(sizeof(int) * (size + 2));
	if (!(new_type))
		return (old_type);
	i = 0;
	while (i < size)
	{
		new_type[i] = old_type[i];
		i++;
	}
	new_type[i++] = value;
	new_type[i] = -1;
	free(old_type);
	return (new_type);
}
