/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:54:13 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/06 17:12:07 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_on_fork_failure(t_cmd *cmd, int *pipes, char **envp, \
	const unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (pipes)
	{
		while (i < (size * 2))
			close(pipes[i++]);
		free(pipes);
	}
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->outfile >= 0)
		close(cmd->outfile);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	clear_cmd_lst(cmd->first);
	envp_free(envp);
	rl_clear_history();
	pwd_accessors("SET", NULL);
}
