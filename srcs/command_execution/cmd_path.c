/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:41:33 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/06 14:55:43 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*create_path(const char *cmd, const char *path_from_envp)
{
	char			*path;
	char			*path_linker;

	if (path_from_envp[ft_strlen(path_from_envp) - 1] != '/')
	{
		path_linker = ft_strjoin(path_from_envp, "/");
		if (!(path_linker))
			return (NULL);
		path = ft_strjoin(path_linker, cmd);
		free(path_linker);
		if (!(path))
			return (NULL);
	}
	else
	{
		path = ft_strjoin(path_from_envp, cmd);
		if (!(path))
			return (NULL);
	}
	return (path);
}

static char	*get_a_working_path(const char *cmd, const char **paths, \
		char *path, int *permission_denied)
{
	unsigned int	i;

	i = 0;
	if (paths[i])
	{
		path = create_path(cmd, paths[i]);
		if (!(path))
			return (NULL);
	}
	i++;
	while (paths[i] && (access(path, F_OK) != 0 || access(path, X_OK) != 0))
	{
		if ((access(path, F_OK) == 0 && access(path, X_OK) != 0 \
		&& *permission_denied == -1))
			*permission_denied = i;
		free(path);
		path = create_path(cmd, paths[i]);
		if (!(path))
			return (NULL);
		i++;
	}
	if ((access(path, F_OK) == 0 && access(path, X_OK) != 0 \
	&& *permission_denied == -1))
		*permission_denied = i;
	return (path);
}

static char	*select_the_right_bad_path(const char *cmd, const char **paths, \
		char *path, int permission_denied)
{
	if (permission_denied != -1)
	{
		free(path);
		path = create_path(cmd, paths[permission_denied]);
		if (!(path))
			return (NULL);
	}
	return (path);
}

static char	*retrieve_cmd_path(const char *cmd, const char **paths)
{
	char	*path;
	int		permission_denied;

	path = ft_strdup(cmd);
	if (!(path))
		return (NULL);
	if (!(paths) || (path[0] && (path[0] == '.' || path[0] == '/')))
		return (path);
	permission_denied = -1;
	free(path);
	path = get_a_working_path(cmd, paths, path, &permission_denied);
	if (!(path))
		return (NULL);
	if ((access(path, F_OK) == 0 && access(path, X_OK) == 0))
		return (path);
	path = select_the_right_bad_path(cmd, paths, path, permission_denied);
	if (!(path))
		return (NULL);
	return (path);
}

void	get_cmds_path(t_cmd *cmd, const char **envp)
{
	char	**paths;

	paths = ft_split(ft_getenv("PATH", envp), ':');
	while (cmd)
	{
		if (cmd->argc != 0)
		{
			if (is_builtin(cmd->argv[0]))
				cmd->path = ft_strdup(cmd->argv[0]);
			if (!(cmd->path))
				cmd->path = retrieve_cmd_path(cmd->argv[0], \
				(const char **)paths);
		}
		cmd = cmd->next;
	}
	envp_free(paths);
}
