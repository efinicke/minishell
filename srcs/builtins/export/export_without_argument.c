/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_without_argument.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:11:17 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/02 13:56:45 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	write_error_msg(void)
{
	perror("minishell: export: write error");
	return (1);
}

static int	env_var_display(const char *env, const int outfile)
{
	unsigned int	i;

	if (env[0] && env[1] && env[0] == '_' && env[1] == '=')
		return (0);
	if (write(outfile, "export ", 7) < 0)
		return (write_error_msg());
	i = 0;
	while (env[i] && env[i] != '=')
		if (write(outfile, env + i++, 1) < 0)
			return (write_error_msg());
	if (env[i])
	{
		if (write(outfile, env + i++, 1) < 0)
			return (write_error_msg());
		if (write(outfile, "\"", 1) < 0)
			return (write_error_msg());
		while (env[i])
			if (write(outfile, env + i++, 1) < 0)
				return (write_error_msg());
		if (write(outfile, "\"", 1) < 0)
			return (write_error_msg());
	}
	if (write(outfile, "\n", 1) < 0)
		return (write_error_msg());
	return (0);
}

static int	sort_env_var_by_ascii_code(const char *var1, const char *var2)
{
	unsigned int	i;

	i = 0;
	while (var1[i] && var2[i] && var1[i] != '=' && var2[i] != '=' \
	&& var1[i] == var2[i])
		i++;
	if (var1[i] == '=' && var2[i] != '=')
		return (-1);
	if (var1[i] != '=' && var2[i] == '=')
		return (1);
	return ((unsigned char)var1[i] - (unsigned char)var2[i]);
}

static int	is_target_variable(const char **envp, const unsigned int envp_size, \
	const unsigned int target_position, const unsigned int i)
{
	unsigned int	j;
	unsigned int	inferiority_counter;

	inferiority_counter = 0;
	j = 0;
	while (envp[j])
	{
		if (sort_env_var_by_ascii_code(envp[i], envp[j]) < 0)
			inferiority_counter++;
		j++;
	}
	if (inferiority_counter == (envp_size - target_position))
		return (1);
	return (0);
}

int	export_without_argument(const char **envp, const int outfile)
{
	unsigned int	i;
	unsigned int	target_position;
	unsigned int	envp_size;

	envp_size = 0;
	while (envp[envp_size])
		envp_size++;
	target_position = 1;
	while (target_position <= envp_size)
	{
		i = 0;
		while (envp[i])
		{
			if (is_target_variable(envp, envp_size, target_position, i))
			{
				if (env_var_display(envp[i], outfile) == 1)
					return (1);
				target_position++;
				break ;
			}
			i++;
		}
	}
	return (0);
}
