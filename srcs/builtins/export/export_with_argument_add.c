/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   export_with_argument_add.c                         :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: spayeur <spayeur@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2022/01/13 13:11:17 by spayeur	       #+#    #+#	      */
/*   Updated: 2022/01/31 13:56:56 by spayeur          ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*alloc_assign_new_variable(const char *var, char **new_envp)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	while (new_envp[i])
		i++;
	j = 0;
	while (var[j])
		j++;
	new_envp[i] = malloc(sizeof(char) * (j + 1));
	if (!(new_envp[i]))
		return (NULL);
	k = 0;
	while (k < j)
	{
		new_envp[i][k] = var[k];
		k++;
	}
	new_envp[i][k] = '\0';
	return (new_envp[i]);
}

char	**add_variable(const char *var, char **old_envp)
{
	char			**new_envp;
	unsigned int	i;

	i = 0;
	while (old_envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!(new_envp))
		return (NULL);
	i = 0;
	while (old_envp[i])
		new_envp[i++] = NULL;
	new_envp[i++] = NULL;
	new_envp[i] = NULL;
	new_envp = envp_sub_alloc((const char **)old_envp, new_envp);
	if (!(new_envp))
		return (NULL);
	new_envp[--i] = alloc_assign_new_variable(var, new_envp);
	if (!(new_envp[i]))
	{
		envp_free(new_envp);
		return (NULL);
	}
	envp_free(old_envp);
	return (new_envp);
}
