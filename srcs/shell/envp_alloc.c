/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:11:17 by spayeur           #+#    #+#             */
/*   Updated: 2022/01/31 14:01:56 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	envp_free(char **envp)
{
	unsigned int	i;

	if (!(envp))
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

char	**envp_sub_alloc(const char **system_envp, char **envp_copy)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (system_envp[i])
	{
		j = 0;
		while (system_envp[i][j])
			j++;
		envp_copy[i] = malloc(sizeof(char) * (j + 1));
		if (!(envp_copy[i]))
		{
			envp_free(envp_copy);
			return (NULL);
		}
		j = 0;
		while (system_envp[i][j])
		{
			envp_copy[i][j] = system_envp[i][j];
			j++;
		}
		envp_copy[i][j] = '\0';
		i++;
	}
	return (envp_copy);
}

char	**envp_alloc(const char **system_envp)
{
	char			**envp_copy;	
	unsigned int	i;

	i = 0;
	while (system_envp[i])
		i++;
	envp_copy = malloc(sizeof(char *) * (i + 1));
	if (!(envp_copy))
		return (NULL);
	i = 0;
	while (system_envp[i])
		envp_copy[i++] = NULL;
	envp_copy[i] = NULL;
	envp_copy = envp_sub_alloc(system_envp, envp_copy);
	if (!(envp_copy))
		return (NULL);
	return (envp_copy);
}
