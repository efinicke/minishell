/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   19_utils_str_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:19:58 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/02 23:45:17 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*alloc_assign_new_str_tab(char *str, char **new_str_tab)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	while (new_str_tab[i])
		i++;
	j = 0;
	while (str[j])
		j++;
	new_str_tab[i] = malloc(sizeof(char) * (j + 1));
	if (!(new_str_tab[i]))
		return (NULL);
	k = 0;
	while (k < j)
	{
		new_str_tab[i][k] = str[k];
		k++;
	}
	new_str_tab[i][k] = '\0';
	return (new_str_tab[i]);
}

char	**str_tab_sub_alloc(const char **old_str_tab, char **str_tab_copy)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (old_str_tab[i])
	{
		j = 0;
		while (old_str_tab[i][j])
			j++;
		str_tab_copy[i] = malloc(sizeof(char) * (j + 1));
		if (!(str_tab_copy[i]))
		{
			clear_str_tab(str_tab_copy);
			return (NULL);
		}
		j = 0;
		while (old_str_tab[i][j])
		{
			str_tab_copy[i][j] = old_str_tab[i][j];
			j++;
		}
		str_tab_copy[i][j] = '\0';
		i++;
	}
	return (str_tab_copy);
}

static char	**check_new_str_tab(char **new_str_tab, unsigned int i)
{
	if (!(new_str_tab[i]))
	{
		clear_str_tab(new_str_tab);
		return (NULL);
	}
	return (new_str_tab);
}

char	**add_str_in_tab(char *str, char **old_str_tab)
{
	char			**new_str_tab;
	unsigned int	i;

	i = 0;
	if (!str)
		return (old_str_tab);
	while (old_str_tab[i])
		i++;
	new_str_tab = malloc(sizeof(char *) * (i + 2));
	if (!(new_str_tab))
		return (NULL);
	i = 0;
	while (old_str_tab[i])
		new_str_tab[i++] = NULL;
	new_str_tab[i++] = NULL;
	new_str_tab[i] = NULL;
	new_str_tab = str_tab_sub_alloc((const char **)old_str_tab, new_str_tab);
	if (!(new_str_tab))
		return (NULL);
	new_str_tab[--i] = alloc_assign_new_str_tab(str, new_str_tab);
	if (!(check_new_str_tab(new_str_tab, i)))
		return (NULL);
	clear_str_tab(old_str_tab);
	return (new_str_tab);
}
