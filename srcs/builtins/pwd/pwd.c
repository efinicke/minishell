/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:19:17 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/03 16:54:54 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	write_error_msg(void)
{
	perror("minishell: pwd: write error");
	return (1);
}

static int	cannot_access_parent_directories_msg(void)
{
	perror("pwd: error retrieving current directory: getcwd: cannot \
access parent directories");
	return (1);
}

static int	error_msg(void)
{
	if (errno == 2)
		return (cannot_access_parent_directories_msg());
	else
		return (write_error_msg());
}

static int	pwd_without_argument(const int outfile)
{
	const char	*pwd = pwd_accessors("GET", NULL);

	if (!(pwd))
		return (error_msg());
	if (write(outfile, pwd, ft_strlen(pwd)) < 0)
		return (write_error_msg());
	if (write(outfile, "\n", 1) < 0)
		return (write_error_msg());
	return (0);
}

int	cmd_pwd(const int argc, const char **argv, const char **envp, \
	const int outfile)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return (pwd_without_argument(outfile));
}
