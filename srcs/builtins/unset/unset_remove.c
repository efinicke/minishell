/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:53:51 by spayeur           #+#    #+#             */
/*   Updated: 2022/01/30 19:56:21 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*sub_alloc(const char **old_envp, char **new_envp, \
		unsigned int i, int found)
{
	unsigned int	j;

	j = 0;
	while (old_envp[i + found][j])
		j++;
	new_envp[i] = malloc(sizeof(char) * (j + 1));
	if (!(new_envp[i]))
	{
		envp_free(new_envp);
		return (NULL);
	}
	j = 0;
	while (old_envp[i + found][j])
	{
		new_envp[i][j] = old_envp[i + found][j];
		j++;
	}
	new_envp[i][j] = '\0';
	return (new_envp[i]);
}

static char	**envp_sub_alloc_except_id(const char **old_envp, char **new_envp, \
		const int id)
{
	int	i;
	int	found;

	found = 0;
	i = 0;
	while (old_envp[i + found])
	{
		if ((i + found) == id)
		{
			found = 1;
			continue ;
		}
		new_envp[i] = sub_alloc(old_envp, new_envp, i, found);
		if (!(new_envp[i]))
			return (NULL);
		i++;
	}
	return (new_envp);
}

char	**remove_variable(char **old_envp, const int id)
{
	char			**new_envp;
	unsigned int	i;

	i = 0;
	while (old_envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i));
	if (!(new_envp))
		return (NULL);
	i = 0;
	while (old_envp[i])
		new_envp[i++] = NULL;
	new_envp = envp_sub_alloc_except_id((const char **)old_envp, \
	new_envp, id);
	if (!(new_envp))
		return (NULL);
	envp_free(old_envp);
	return (new_envp);
}
