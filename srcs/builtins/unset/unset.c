/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:53:51 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/07 12:49:26 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	invalid_identifier_msg(const char *identifier)
{
	const char		*minishell_unset = "minishell: unset: `";
	const char		*not_valid = "': not a valid identifier";
	char			*msg;
	unsigned int	i;
	unsigned int	j;

	msg = malloc(sizeof(char) * (ft_strlen(minishell_unset) + \
	ft_strlen(identifier) + ft_strlen(not_valid) + 2));
	if (!(msg))
		return (1);
	i = 0;
	j = 0;
	while (minishell_unset && minishell_unset[j])
		msg[i++] = minishell_unset[j++];
	j = 0;
	while (identifier && identifier[j])
		msg[i++] = identifier[j++];
	j = 0;
	while (not_valid && not_valid[j])
		msg[i++] = not_valid[j++];
	msg[i++] = '\n';
	msg[i] = '\0';
	write(STDERR_FILENO, msg, ft_strlen(msg));
	free(msg);
	return (1);
}

static int	is_valid_identifier(const char *identifier)
{
	unsigned int	i;

	i = 0;
	if (!(ft_isalpha(identifier[i])) && identifier[i] != '_')
		return (0);
	i++;
	while (identifier[i])
	{
		if (!(ft_isalpha(identifier[i])) \
		&& !(ft_isdigit(identifier[i])) && identifier[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	unset_with_argument(const char **argv, char ***envp)
{
	int				id;
	int				return_code;
	unsigned int	i;

	return_code = 0;
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '_' && ft_strlen(argv[i]) == 1 && i++)
			continue ;
		if (is_valid_identifier(argv[i]))
		{
			id = ft_getenv_id(argv[i], (const char **)*envp);
			if (id != -1)
			{
				*envp = remove_variable(*envp, id);
				if (!(*envp))
					return (EXIT_FAILURE);
			}
		}
		else
			return_code = invalid_identifier_msg(argv[i]);
		i++;
	}
	return (return_code);
}

int	cmd_unset(const int argc, const char **argv, char ***envp)
{
	if (argc > 1)
		return (unset_with_argument(argv, envp));
	return (0);
}
