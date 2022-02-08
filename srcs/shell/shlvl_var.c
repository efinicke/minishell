/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:14:16 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/07 14:52:19 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_a_number(const char *string)
{
	unsigned int	i;

	i = 0;
	if (!(string))
		return (0);
	i = 0;
	while (string[i] && ft_isspace(string[i]))
		i++;
	if (string[i] == '+' || string[i] == '-')
		i++;
	while (string[i] && ft_isdigit(string[i]))
		i++;
	while (string[i] && ft_isspace(string[i]))
		i++;
	if (string[i])
		return (0);
	return (1);
}

void	shlvl_too_high(const int shlvl_int)
{
	char	*shlvl_char_allocated;

	write(STDERR_FILENO, "minishell: warning: shell level ", 32);
	shlvl_char_allocated = ft_itoa(shlvl_int);
	if (shlvl_char_allocated)
	{
		write(STDERR_FILENO, "(", 1);
		write(STDERR_FILENO, shlvl_char_allocated, \
		ft_strlen(shlvl_char_allocated));
		write(STDERR_FILENO, ") ", 2);
		free(shlvl_char_allocated);
	}
	write(STDERR_FILENO, "too high, resetting to 1\n", 25);
}

int	get_shlvl(char ***envp)
{
	const char	*shlvl_char = ft_getenv("SHLVL", (const char **)*envp);
	int			shlvl_int;

	if (shlvl_char)
		shlvl_int = ft_atoi(shlvl_char);
	else
		shlvl_int = 0;
	shlvl_int++;
	if (shlvl_int < 0 || (shlvl_char && !(is_a_number(shlvl_char))))
		shlvl_int = 0;
	if (shlvl_int > 999)
	{
		shlvl_too_high(shlvl_int);
		shlvl_int = 1;
	}
	return (shlvl_int);
}

void	set_shlvl_var(char ***envp)
{
	char	*export_shlvl[3];
	char	*shlvl_itoa;
	int		shlvl_int;

	shlvl_int = get_shlvl(envp);
	shlvl_itoa = ft_itoa(shlvl_int);
	export_shlvl[0] = "export";
	export_shlvl[1] = ft_strjoin("SHLVL=", shlvl_itoa);
	export_shlvl[2] = NULL;
	free(shlvl_itoa);
	if (export_shlvl[1])
	{
		cmd_export(2, (const char **)export_shlvl, envp, STDOUT_FILENO);
		free(export_shlvl[1]);
	}
}
