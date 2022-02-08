/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_utils_stderr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 23:39:02 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/06 16:49:02 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	send_error(char *error_message)
{
	char	*error_form;

	error_form = "minishell: ";
	write(2, &(*error_form), str_len(error_form));
	write(2, &(*error_message), str_len(error_message));
	write(2, "\n", 2);
}
