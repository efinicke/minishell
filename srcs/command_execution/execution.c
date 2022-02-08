/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:43:46 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/06 19:23:37 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	status_to_return_value(t_cmd *last_cmd, int status)
{
	if (last_cmd->argc == 0)
		return (0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status) && WCOREDUMP(status))
		return (131);
	else if (WIFSIGNALED(status) && WTERMSIG(status))
		return (130);
	return (-1);
}

static int	main_process_waiting_room(t_cmd *cmd, int *pipes, unsigned int size)
{
	t_cmd				*last_cmd;
	int					status;
	unsigned int		i;

	i = 0;
	while (i < (size * 2))
		close(pipes[i++]);
	while (cmd)
	{
		if (cmd->argc > 0 && waitpid(cmd->pid, &status, 0) < 0)
		{
			perror("minishell: wait");
			return (143);
		}
		last_cmd = cmd;
		cmd = cmd->next;
	}
	return (status_to_return_value(last_cmd, status));
}

static int	exec_cmds(t_cmd *cmd, int *pipes, char **envp)
{
	const unsigned int	size = get_cmd_list_size(cmd);
	unsigned int		i;
	unsigned int		j;

	i = 0;
	while (i < size)
	{
		if (pipe(pipes + (i * 2)) < 0)
		{
			j = 0;
			while (j < (i * 2))
				close(pipes[j++]);
			perror("minishell: pipe error");
			return (129);
		}
		i++;
	}
	here_doc_implementation(cmd, pipes, size, envp);
	if (basic_execution(cmd, pipes, envp, size) < 0)
		return (254);
	return (main_process_waiting_room(cmd, pipes, size));
}

int	execution(t_cmd *cmd, char ***envp)
{
	const unsigned int	size = get_cmd_list_size(cmd);
	int					*pipes;
	int					return_code;

	get_cmds_path(cmd, (const char **)*envp);
	pipes = NULL;
	if (size == 1 && cmd->argc == 0)
	{
		here_doc_implementation(cmd, pipes, 0, *envp);
		if (open_all_io_files(cmd, pipes, 0, 0) < 0)
			return (EXIT_FAILURE);
		return (0);
	}
	else if (size == 1 && is_builtin(cmd->path))
		return (exec_builtin(cmd, envp, size));
	else
	{
		pipes = malloc(sizeof(int) * (size * 2));
		if (!(pipes))
			return (EXIT_FAILURE);
		return_code = exec_cmds(cmd, pipes, *envp);
		free(pipes);
	}
	return (return_code);
}
