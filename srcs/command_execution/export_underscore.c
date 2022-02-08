/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_underscore.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:41:28 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/02 13:40:47 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**create_export_underscore(const char *path)
{
	char	**export;

	export = malloc(sizeof(char **) * 3);
	if (!(export))
		return (NULL);
	export[0] = ft_strdup("export");
	if (!(export[0]))
	{
		free(export);
		return (NULL);
	}
	export[1] = ft_strjoin("_=", path);
	if (!(export[1]))
	{
		free(export[0]);
		free(export);
		return (NULL);
	}
	export[2] = NULL;
	return (export);
}

void	export_underscore(const char *path, char ***envp)
{
	char	**export_underscore;

	export_underscore = create_export_underscore(path);
	if (export_underscore)
	{
		cmd_export(2, (const char **)export_underscore, envp, STDOUT_FILENO);
		envp_free(export_underscore);
	}
}
