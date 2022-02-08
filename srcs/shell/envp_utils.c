/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:11:17 by spayeur           #+#    #+#             */
/*   Updated: 2022/01/31 14:02:09 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static unsigned int	ft_getenv_len(const char *env)
{
	unsigned int	i;

	if (!(env))
		return (0);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

// char	*ft_getenv(const char *name, char **envp);
// If it exists, the value of the variable named [name] is returned otherwise
// NULL is returned.
const char	*ft_getenv(const char *name, const char **envp)
{
	unsigned int	id;
	unsigned int	j;

	id = 0;
	while (envp[id] && (ft_getenv_len(envp[id]) != ft_getenv_len(name) \
	|| ft_strncmp(envp[id], name, ft_getenv_len(name)) != 0))
		id++;
	if (!(envp[id]))
		return (NULL);
	j = 0;
	while (envp[id][j] != '=')
		j++;
	j++;
	return (envp[id] + j);
}

// int	ft_getenv_id(const char *name, char **envp);
// If it exists, the id in the string table [envp] of the variable named [name]
// is returned, otherwise -1 is returned.
int	ft_getenv_id(const char *name, const char **envp)
{
	unsigned int	id;

	id = 0;
	while (envp[id] && (ft_getenv_len(envp[id]) != ft_getenv_len(name) \
	|| ft_strncmp(envp[id], name, ft_getenv_len(name)) != 0))
		id++;
	if (!(envp[id]))
		return (-1);
	else
		return (id);
}
