/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:15:54 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/07 12:49:51 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	numeric_argument_required(const char *argument)
{
	const char		*minishell_exit = "minishell: exit: ";
	const char		*numeric_argument = ": numeric argument required";
	char			*msg;
	unsigned int	i;
	unsigned int	j;

	msg = malloc(sizeof(char) * (ft_strlen(minishell_exit) + \
	ft_strlen(argument) + ft_strlen(numeric_argument) + 2));
	if (!(msg))
		return ;
	i = 0;
	j = 0;
	while (minishell_exit && minishell_exit[j])
		msg[i++] = minishell_exit[j++];
	j = 0;
	while (argument && argument[j])
		msg[i++] = argument[j++];
	j = 0;
	while (numeric_argument && numeric_argument[j])
		msg[i++] = numeric_argument[j++];
	msg[i++] = '\n';
	msg[i] = '\0';
	write(STDERR_FILENO, msg, ft_strlen(msg));
	free(msg);
}

static int	mix_max_border_validity(const char *exit_code, unsigned int i, \
		unsigned int negative)
{
	if (negative)
	{
		if (ft_strncmp(exit_code + i, "9223372036854775808", 19) > 0)
			return (0);
	}
	else
	{
		if (ft_strncmp(exit_code + i, "9223372036854775807", 19) > 0)
			return (0);
	}
	return (1);
}

static int	min_max_validity(const char *exit_code)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	negative;

	negative = 0;
	i = 0;
	while (exit_code[i] && ft_isspace(exit_code[i]))
		i++;
	if (exit_code[i] == '+' || exit_code[i] == '-')
	{
		if (exit_code[i] == '-')
			negative = 1;
		i++;
	}
	j = 0;
	while (exit_code[i + j] && ft_isdigit(exit_code[i + j]))
		j++;
	if (j > 19 || j < 1)
		return (0);
	if (j < 19)
		return (1);
	if (mix_max_border_validity(exit_code, i, negative) == 0)
		return (0);
	return (1);
}

int	exit_code_validity(const char *exit_code)
{
	unsigned int	i;

	i = 0;
	while (exit_code[i] && ft_isspace(exit_code[i]))
		i++;
	if (!(exit_code[i]))
		return (0);
	if (exit_code[i] == '+' || exit_code[i] == '-')
		i++;
	while (exit_code[i] && !(ft_isspace(exit_code[i])))
	{
		if (!(ft_isdigit(exit_code[i])))
			return (0);
		i++;
	}
	while (exit_code[i] && ft_isspace(exit_code[i]))
		i++;
	if (exit_code[i])
		return (0);
	if (min_max_validity(exit_code) == 0)
		return (0);
	return (1);
}
