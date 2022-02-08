/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: spayeur <spayeur@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2022/01/17 17:08:20 by spayeur	       #+#    #+#	      */
/*   Updated: 2022/02/07 11:55:53 by spayeur          ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	too_many_arguments_msg(int is_fork)
{
	if (!(is_fork))
		write(STDERR_FILENO, "exit\n", 5);
	write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
	return (1);
}

static void	invalid_exit_code_msg(t_cmd *cmd, char **envp, int *pipes, \
		int is_fork)
{
	const char			*exit_code = cmd->argv[1];
	const unsigned int	size = get_cmd_list_size(cmd->first);

	if (!(is_fork))
		write(STDERR_FILENO, "exit\n", 5);
	numeric_argument_required(exit_code);
	free_on_fork_failure(cmd, pipes, envp, size);
	exit(2);
}

static long long int	ll_atoi(const char *number_str)
{
	long long int	number;
	int				sign;
	unsigned int	i;

	number = 0;
	sign = 1;
	i = 0;
	while (number_str[i] && ft_isspace(number_str[i]))
		i++;
	if (number_str[i] == '+' || number_str[i] == '-')
	{
		if (number_str[i] == '-')
			sign *= -1;
		i++;
	}
	while ('0' <= number_str[i] && number_str[i] <= '9')
	{
		number *= 10;
		number += number_str[i] - '0';
		i++;
	}
	return (number * sign);
}

static void	exit_with_argument(t_cmd *cmd, char **envp, int *pipes, int is_fork)
{
	const char			*exit_string = cmd->argv[1];
	const unsigned int	size = get_cmd_list_size(cmd->first);
	int					exit_code;
	unsigned int		i;

	i = 0;
	while (exit_string[i] && ft_isspace(exit_string[i]))
		i++;
	if (exit_code_validity(exit_string + i))
	{
		exit_code = ll_atoi(exit_string) % 256;
		if (!(is_fork))
			write(STDERR_FILENO, "exit\n", 5);
		free_on_fork_failure(cmd, pipes, envp, size);
		exit(exit_code);
	}
	else
		invalid_exit_code_msg(cmd, envp, pipes, is_fork);
}

int	cmd_exit(t_cmd *cmd, char **envp, int *pipes, int is_fork)
{
	const unsigned int	size = get_cmd_list_size(cmd->first);

	if (cmd->argc > 2)
		return (too_many_arguments_msg(is_fork));
	else if (cmd->argc == 2)
		exit_with_argument(cmd, envp, pipes, is_fork);
	if (!(is_fork))
		write(STDERR_FILENO, "exit\n", 5);
	free_on_fork_failure(cmd, pipes, envp, size);
	exit(0);
	return (0);
}
