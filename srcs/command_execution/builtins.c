/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:53:12 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/06 17:27:26 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(const char *cmd_path)
{
	if (ft_strncmp(cmd_path, "echo", 4) == 0 && ft_strlen(cmd_path) == 4)
		return (1);
	if (ft_strncmp(cmd_path, "cd", 2) == 0 && ft_strlen(cmd_path) == 2)
		return (1);
	if (ft_strncmp(cmd_path, "pwd", 3) == 0 && ft_strlen(cmd_path) == 3)
		return (1);
	if (ft_strncmp(cmd_path, "export", 6) == 0 && ft_strlen(cmd_path) == 6)
		return (1);
	if (ft_strncmp(cmd_path, "unset", 5) == 0 && ft_strlen(cmd_path) == 5)
		return (1);
	if (ft_strncmp(cmd_path, "env", 3) == 0 && ft_strlen(cmd_path) == 3)
		return (1);
	if (ft_strncmp(cmd_path, "exit", 4) == 0 && ft_strlen(cmd_path) == 4)
		return (1);
	return (0);
}

static int	select_builtin(t_cmd *cmd, char ***envp, int *pipes, int is_fork)
{
	if (ft_strncmp(cmd->path, "echo", 4) == 0 && ft_strlen(cmd->path) == 4)
		return (cmd_echo(cmd->argc, (const char **)cmd->argv, cmd->outfile));
	if (ft_strncmp(cmd->path, "cd", 2) == 0 && ft_strlen(cmd->path) == 2)
		return (cmd_cd(cmd->argc, (const char **)cmd->argv, envp, \
		cmd->outfile));
	if (ft_strncmp(cmd->path, "pwd", 3) == 0 && ft_strlen(cmd->path) == 3)
		return (cmd_pwd(cmd->argc, (const char **)cmd->argv, \
		(const char **)*envp, cmd->outfile));
	if (ft_strncmp(cmd->path, "export", 6) == 0 && ft_strlen(cmd->path) == 6)
		return (cmd_export(cmd->argc, (const char **)cmd->argv, envp, \
		cmd->outfile));
	if (ft_strncmp(cmd->path, "unset", 5) == 0 && ft_strlen(cmd->path) == 5)
		return (cmd_unset(cmd->argc, (const char **)cmd->argv, envp));
	if (ft_strncmp(cmd->path, "env", 3) == 0 && ft_strlen(cmd->path) == 3)
		return (cmd_env(cmd->argc, (const char **)cmd->argv, \
		(const char **)*envp, cmd->outfile));
	if (ft_strncmp(cmd->path, "exit", 4) == 0 && ft_strlen(cmd->path) == 4)
		return (cmd_exit(cmd, *envp, pipes, is_fork));
	return (EXIT_FAILURE);
}

int	exec_builtin(t_cmd *cmd, char ***envp, const unsigned int size)
{
	int	pipes[2];

	pipes[0] = -1;
	pipes[1] = -1;
	here_doc_implementation(cmd, pipes, 0, *envp);
	if (open_all_io_files(cmd, pipes, size, 1) < 0)
		return (EXIT_FAILURE);
	if (cmd->infile == -1)
		cmd->infile = STDIN_FILENO;
	if (cmd->outfile == -1)
		cmd->outfile = STDOUT_FILENO;
	export_underscore(cmd->path, envp);
	return (select_builtin(cmd, envp, NULL, 0));
}

int	exec_builtin_in_fork(t_cmd *cmd, int *pipes, char **envp, \
	const unsigned int size)
{
	int	return_code;

	if (cmd->infile == -1)
		cmd->infile = STDIN_FILENO;
	if (cmd->outfile == -1)
		cmd->outfile = STDOUT_FILENO;
	return_code = select_builtin(cmd, &envp, pipes, 1);
	free_on_fork_failure(cmd, pipes, envp, size);
	exit(return_code);
}
