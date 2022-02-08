/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   export_with_argument.c                             :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: spayeur <spayeur@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2022/01/13 13:11:17 by spayeur	       #+#    #+#	      */
/*   Updated: 2022/02/07 12:50:28 by spayeur          ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	invalid_identifier_msg(const char *identifier)
{
	const char		*minishell_export = "minishell: export: `";
	const char		*not_valid = "': not a valid identifier";
	char			*msg;
	unsigned int	i;
	unsigned int	j;

	msg = malloc(sizeof(char) * (ft_strlen(minishell_export) + \
	ft_strlen(identifier) + ft_strlen(not_valid) + 2));
	if (!(msg))
		return (1);
	i = 0;
	j = 0;
	while (minishell_export && minishell_export[j])
		msg[i++] = minishell_export[j++];
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
	while (identifier[i] && identifier[i] != '=')
	{
		if (!(ft_isalpha(identifier[i])) \
		&& !(ft_isdigit(identifier[i])) && identifier[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	add_or_replace(const char *var, char ***envp)
{
	int	id;

	id = ft_getenv_id(var, (const char **)*envp);
	if (id >= 0)
	{
		if (!(replace_variable(var, *envp, id)))
			return (EXIT_FAILURE);
	}
	else
	{	
		*envp = add_variable(var, *envp);
		if (!(*envp))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	export_with_argument(const char **argv, char ***envp)
{
	int				return_code;
	unsigned int	i;

	return_code = 0;
	i = 1;
	while (argv[i])
	{
		if (is_valid_identifier(argv[i]))
		{
			if (add_or_replace(argv[i], \
			envp) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
			return_code = invalid_identifier_msg(argv[i]);
		i++;
	}
	return (return_code);
}
