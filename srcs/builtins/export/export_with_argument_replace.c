/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   export_with_argument_replace.c                     :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: spayeur <spayeur@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2022/01/13 13:11:17 by spayeur	       #+#    #+#	      */
/*   Updated: 2022/01/31 13:56:56 by spayeur          ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*alloc_assign_new_value(const char *var, \
		const unsigned int size)
{
	char			*var_allocated;
	unsigned int	i;

	var_allocated = malloc(sizeof(char) * (size + 1));
	if (!(var_allocated))
		return (NULL);
	i = 0;
	while (var[i])
	{
		var_allocated[i] = var[i];
		i++;
	}
	var_allocated[i] = '\0';
	return (var_allocated);
}

char	*replace_variable(const char *var, char **envp, const int id)
{
	char			*var_allocated;
	unsigned int	i;

	i = 0;
	while (var[i] && var[i] != '=' \
	&& !(ft_isspace(var[i])))
		i++;
	if (!(var[i]) || var[i] != '=')
		return (envp[id]);
	while (var[i])
		i++;
	var_allocated = alloc_assign_new_value(var, (const unsigned int)i);
	if (!(var_allocated))
		return (NULL);
	free(envp[id]);
	envp[id] = var_allocated;
	return (envp[id]);
}
