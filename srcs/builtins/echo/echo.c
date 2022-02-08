/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:53:10 by spayeur           #+#    #+#             */
/*   Updated: 2022/01/30 19:56:18 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	write_error_msg(void)
{
	perror("minishell: echo: write error");
	return (1);
}

static int	parse_options(const char **argv, unsigned int *addr_i)
{
	int				return_code;
	unsigned int	j;

	return_code = 1;
	while (argv[*addr_i])
	{
		j = 0;
		if (argv[*addr_i][j] != '-')
			return (return_code);
		j++;
		while (argv[*addr_i][j] && argv[*addr_i][j] == 'n')
			j++;
		if (argv[*addr_i][j])
			return (return_code);
		return_code = 0;
		*addr_i += 1;
	}
	return (return_code);
}

static int	echo_with_argument(const char **argv, const int outfile)
{
	int				write_new_line;
	int				write_space;
	unsigned int	i;

	i = 1;
	write_space = 0;
	write_new_line = parse_options(argv, &i);
	while (argv[i])
	{
		if (write_space)
		{
			if (write(outfile, " ", 1) < 0)
				return (write_error_msg());
		}
		else
			write_space = 1;
		if (write(outfile, argv[i], ft_strlen(argv[i])) < 0)
			return (write_error_msg());
		i++;
	}
	if (write_new_line && write(outfile, "\n", 1) < 0)
		return (write_error_msg());
	return (0);
}

int	cmd_echo(const int argc, const char **argv, const int outfile)
{
	if (argc > 1)
		return (echo_with_argument(argv, outfile));
	if (write(outfile, "\n", 1) < 0)
		return (write_error_msg());
	return (0);
}
