/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:21:29 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/07 12:34:18 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	eof_warning_msg(const char *limiter)
{
	write(STDERR_FILENO, "minishell: warning: here-document ", 34);
	write(STDERR_FILENO, "delimited by end-of-file (wanted `", 35);
	write(STDERR_FILENO, limiter, ft_strlen(limiter));
	write(STDERR_FILENO, "')\n", 3);
}

static void	real_here_doc(const char *limiter, int fd, char **envp)
{
	char	*line;
	t_lx	*datas;

	datas = init_datas_struct(NULL);
	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(line)) == 0 \
		&& ft_strlen(line) == ft_strlen(limiter))
		{
			free(line);
			clear_datas_struct(datas);
			close(fd);
			return ;
		}
		line = replace_dollar_var_by_val(line, envp, datas);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	eof_warning_msg(limiter);
	free(line);
	clear_datas_struct(datas);
	return ;
}

static void	fake_here_doc(const char *limiter)
{
	char	*line;

	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(line)) == 0 \
		&& ft_strlen(line) == ft_strlen(limiter))
		{
			free(line);
			return ;
		}
		free(line);
		line = readline("> ");
	}
	eof_warning_msg(limiter);
	free(line);
	return ;
}

static void	here_doc_selector(t_cmd *cmd, int *pipes, const unsigned int size, \
		char **envp)
{
	const unsigned int	pos = size - get_cmd_list_size(cmd);
	int					real_one;
	int					i;

	i = 0;
	while (cmd->file[i])
		i++;
	real_one = -1;
	while (--i >= 0 && cmd->type[i] != 1)
		if (cmd->type[i] == 0)
			break ;
	if (i >= 0 && cmd->type[i] == 1)
		real_one = i;
	i = 0;
	while (cmd->file[i])
	{
		if (cmd->type[i] == 1)
		{
			if (i == real_one)
				real_here_doc(cmd->file[i], pipes[((pos * 2) + 1)], envp);
			else
				fake_here_doc(cmd->file[i]);
		}
		i++;
	}
}

void	here_doc_implementation(t_cmd *cmd, int *pipes, \
	const unsigned int size, char **envp)
{
	unsigned int	i;

	set_signals(1);
	if (size >= 1)
	{
		while (cmd)
		{
			here_doc_selector(cmd, pipes, size, envp);
			cmd = cmd->next;
		}
	}
	else
	{
		i = 0;
		while (cmd->file[i])
		{
			if (cmd->type[i] == 1)
				fake_here_doc(cmd->file[i]);
			i++;
		}
	}
	set_signals(2);
}
