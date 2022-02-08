/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:14:16 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/07 14:14:20 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	minishell_init_error_msg(void)
{
	perror("minishell-init: error retrieving current directory: \
getcwd: cannot access parent directories");
	return (1);
}

void	set_pwd_var(char ***envp)
{
	char	*export_pwd[3];

	export_pwd[0] = "export";
	export_pwd[1] = ft_strjoin("PWD=", pwd_accessors("GET", NULL));
	export_pwd[2] = NULL;
	if (export_pwd[1])
	{
		cmd_export(2, (const char **)export_pwd, envp, STDOUT_FILENO);
		free(export_pwd[1]);
	}
	else
		minishell_init_error_msg();
}
