/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:06:32 by spayeur           #+#    #+#             */
/*   Updated: 2022/01/30 19:56:19 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	write_error_msg(void)
{
	perror("env: write error");
	return (125);
}

static int	env_var_display(const char *env, const int outfile)
{
	unsigned int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!(env[i]))
		return (0);
	if (write(outfile, env, ft_strlen(env)) < 0)
		return (write_error_msg());
	if (write(outfile, "\n", 1) < 0)
		return (write_error_msg());
	return (0);
}

static int	env_without_argument(const char **envp, const int outfile)
{
	unsigned int	i;

	i = 0;
	while (envp[i])
	{
		if (env_var_display(envp[i], outfile) == 125)
			return (125);
		i++;
	}
	return (0);
}

int	cmd_env(const int argc, const char **argv, const char **envp, \
	const int outfile)
{
	(void)argc;
	(void)argv;
	return (env_without_argument(envp, outfile));
}
