/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:41:28 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/06 18:33:04 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	fork_error_msg(void)
{
	pid_t			pid;
	unsigned int	i;

	i = 0;
	while (i < 4 && pid < 0)
	{
		perror("minishell: fork: retry");
		pid = fork();
		i++;
	}
	if (pid < 0)
	{
		perror("minishell: fork");
		return (-1);
	}
	return (pid);
}

static void	io_redirection(t_cmd *cmd, int *pipes, const unsigned int size)
{
	const unsigned int	pos = size - get_cmd_list_size(cmd);
	unsigned int		default_io_redirection[2];

	default_io_redirection[0] = 1;
	default_io_redirection[1] = 1;
	if (pos == 0 && pos == size - 1)
	{
		default_io_redirection[0] = 0;
		default_io_redirection[1] = 0;
	}
	else if (pos == 0)
		default_io_redirection[0] = 0;
	else if (pos == size - 1)
		default_io_redirection[1] = 0;
	if (cmd->infile >= 0)
		dup2(cmd->infile, STDIN_FILENO);
	else if (default_io_redirection[0])
		dup2(pipes[(pos * 2)], STDIN_FILENO);
	if (cmd->outfile >= 0)
		dup2(cmd->outfile, STDOUT_FILENO);
	else if (default_io_redirection[1] && cmd->next && cmd->next->infile != -42)
		dup2(pipes[(((pos + 1) * 2)) + 1], STDOUT_FILENO);
	else if (default_io_redirection[1] && cmd->next && cmd->next->infile == -42)
		dup2(open("/dev/null", O_CREAT | O_WRONLY | O_TRUNC, 0644), \
		STDOUT_FILENO);
}

static int	exec_cmd(t_cmd *cmd, int *pipes, char **envp, \
		const unsigned int size)
{
	unsigned int	i;

	cmd->pid = fork();
	if (cmd->pid < 0)
		cmd->pid = fork_error_msg();
	if (cmd->pid < 0)
		return (-1);
	if (cmd->pid > 0)
		return (0);
	if (open_all_io_files(cmd, pipes, size, 1) < 0)
	{
		free_on_fork_failure(cmd, pipes, envp, size);
		exit(EXIT_FAILURE);
	}
	io_redirection(cmd, pipes, size);
	export_underscore(cmd->path, &envp);
	if (is_builtin(cmd->path))
		exec_builtin_in_fork(cmd, pipes, envp, size);
	i = 0;
	while (i < (size * 2))
		close(pipes[i++]);
	execve(cmd->path, cmd->argv, envp);
	return (cmd_error(cmd, pipes, envp, size));
}

static void	hyphen42(t_cmd *cmd)
{
	unsigned int	i;

	i = 0;
	while (cmd)
	{
		i = 0;
		while (cmd->file[i])
		{
			if (((cmd->type[i] == 0 && (ft_strncmp(cmd->file[i], \
			"/dev/stdin", ft_strlen(cmd->file[i])) != 0 \
			|| ft_strlen(cmd->file[i]) != 10)) || (cmd->type[i] == 1)))
			{
				cmd->infile = -42;
				break ;
			}
			i++;
		}
		cmd = cmd->next;
	}
}

int	basic_execution(t_cmd *cmd, int *pipes, char **envp, \
	const unsigned int size)
{
	unsigned int	i;

	hyphen42(cmd);
	i = 0;
	while (i < size)
	{
		if (cmd->argc == 0)
			open_all_io_files(cmd, pipes, size, 0);
		else
		{
			if (exec_cmd(cmd, pipes, envp, size) < 0)
				return (-1);
		}
		cmd = cmd->next;
		i++;
	}
	return (0);
}
