/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:46:11 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/07 10:30:33 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cmd_error_msg(const char *minishell, const char *cmd, \
		const char *pre_error, const char *error)
{
	char			*msg;
	unsigned int	i;
	unsigned int	j;

	msg = malloc(sizeof(char) * (ft_strlen(minishell) + ft_strlen(cmd) + \
	ft_strlen(pre_error) + ft_strlen(error) + 2));
	if (!(msg))
		return ;
	i = 0;
	j = 0;
	while (minishell && minishell[j])
		msg[i++] = minishell[j++];
	j = 0;
	while (cmd && cmd[j])
		msg[i++] = cmd[j++];
	j = 0;
	while (pre_error && pre_error[j])
		msg[i++] = pre_error[j++];
	j = 0;
	while (error && error[j])
		msg[i++] = error[j++];
	msg[i++] = '\n';
	msg[i] = '\0';
	write(STDERR_FILENO, msg, ft_strlen(msg));
	free(msg);
}

static void	cmd_error_enoent(t_cmd *cmd, int *pipes, char **envp, \
		const unsigned int size)
{
	if (ft_getenv_id("PATH", (const char **)envp) == -1 \
	|| (ft_strnstr(*(cmd->argv), "/", ft_strlen(*(cmd->argv)))))
	{
		cmd_error_msg("minishell: ", *(cmd->argv), NULL, \
		": No such file or directory");
		free_on_fork_failure(cmd, pipes, envp, size);
		exit(127);
	}
	else
	{
		cmd_error_msg("minishell: ", *(cmd->argv), NULL, ": command not found");
		free_on_fork_failure(cmd, pipes, envp, size);
		exit(127);
	}
}

static void	cmd_error_eacces(t_cmd *cmd, int *pipes, char **envp, \
		const unsigned int size)
{
	DIR	*dir;

	dir = opendir(*(cmd->argv));
	if (!(dir))
	{
		if (ft_strlen(*(cmd->argv)) == 0)
			cmd_error_enoent(cmd, pipes, envp, size);
		cmd_error_msg("minishell: ", *(cmd->argv), NULL, ": Permission denied");
		free_on_fork_failure(cmd, pipes, envp, size);
		exit(126);
	}
	else
	{
		closedir(dir);
		cmd_error_msg("minishell: ", *(cmd->argv), NULL, ": Is a directory");
		free_on_fork_failure(cmd, pipes, envp, size);
		exit(126);
	}
}

int	cmd_error(t_cmd *cmd, int *pipes, char **envp, const unsigned int size)
{
	if (errno == EACCES)
		cmd_error_eacces(cmd, pipes, envp, size);
	else if (errno == ENOENT)
		cmd_error_enoent(cmd, pipes, envp, size);
	else
	{
		cmd_error_msg("minishell: ", *(cmd->argv), ": ", strerror(errno));
		free_on_fork_failure(cmd, pipes, envp, size);
		exit(126);
	}
	return (EXIT_FAILURE);
}
