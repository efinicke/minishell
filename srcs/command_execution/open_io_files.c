/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_io_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:03:05 by spayeur           #+#    #+#             */
/*   Updated: 2022/01/30 19:56:15 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	file_error_msg(const char *minishell, const char *filename)
{
	char			*msg;
	unsigned int	i;
	unsigned int	j;

	msg = malloc(sizeof(char) * (ft_strlen(minishell) + \
	ft_strlen(filename) + 1));
	if (!(msg))
		return (-1);
	i = 0;
	while (minishell[i])
	{
		msg[i] = minishell[i];
		i++;
	}
	j = 0;
	while (filename[j])
	{
		msg[i + j] = filename[j];
		j++;
	}
	msg[i + j] = '\0';
	perror(msg);
	free(msg);
	return (-1);
}

static int	open_infile(const char *file, const int type)
{
	int	fd;

	if (type == 0)
	{
		if (access(file, F_OK) != 0 || access(file, R_OK) != 0)
			return (file_error_msg("minishell: ", file));
		fd = open(file, O_RDONLY);
		if (fd < 0)
			return (file_error_msg("minishell: ", file));
		close(fd);
	}
	return (0);
}

static int	open_outfile(const char *file, const int type)
{
	int	fd;

	if (type == 2)
	{
		if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
			return (file_error_msg("minishell: ", file));
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (file_error_msg("minishell: ", file));
		close(fd);
	}
	else if (type == 3)
	{
		if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
			return (file_error_msg("minishell: ", file));
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			return (file_error_msg("minishell: ", file));
		close(fd);
	}
	return (0);
}

static void	set_cmd_infile_outfile(t_cmd *cmd, int *pipes, \
		const unsigned int size, const int io_files_index[2])
{
	const unsigned int	pos = size - get_cmd_list_size(cmd);

	if (io_files_index[0] != -1 \
	&& (ft_strncmp(cmd->file[io_files_index[0]], "/dev/stdin", \
	ft_strlen(cmd->file[io_files_index[0]])) != 0 \
	|| ft_strlen(cmd->file[io_files_index[0]]) != 10 \
	|| cmd->type[io_files_index[0]] == 1))
	{
		if (cmd->type[io_files_index[0]] == 0)
			cmd->infile = open(cmd->file[io_files_index[0]], O_RDONLY);
		if (cmd->type[io_files_index[0]] == 1)
			cmd->infile = pipes[(pos * 2)];
	}
	if (io_files_index[1] != -1 \
	&& (ft_strncmp(cmd->file[io_files_index[1]], "/dev/stdout", \
	ft_strlen(cmd->file[io_files_index[1]])) != 0 \
	|| ft_strlen(cmd->file[io_files_index[1]]) != 11))
	{	
		if (cmd->type[io_files_index[1]] == 2)
			cmd->outfile = open(cmd->file[io_files_index[1]], \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (cmd->type[io_files_index[1]] == 3)
			cmd->outfile = open(cmd->file[io_files_index[1]], \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
}

int	open_all_io_files(t_cmd *cmd, int *pipes, const unsigned int size, \
	const unsigned int set_cmd_io)
{
	int				io_files_index[2];
	unsigned int	i;

	io_files_index[0] = -1;
	io_files_index[1] = -1;
	i = 0;
	while (cmd->file[i])
	{
		if (cmd->type[i] == 0 || cmd->type[i] == 1)
		{
			if (open_infile(cmd->file[i], cmd->type[i]) < 0)
				return (-1);
			io_files_index[0] = i;
		}
		else if (cmd->type[i] == 2 || cmd->type[i] == 3)
		{
			if (open_outfile(cmd->file[i], cmd->type[i]) < 0)
				return (-1);
			io_files_index[1] = i;
		}
		i++;
	}
	if (set_cmd_io)
		set_cmd_infile_outfile(cmd, pipes, size, io_files_index);
	return (0);
}
