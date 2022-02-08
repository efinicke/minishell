/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:35:46 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/07 12:50:11 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	cd_perror_msg(const char *string)
{
	const char		*minishell_cd = "minishell: cd: ";
	char			*msg;
	unsigned int	i;
	unsigned int	j;

	msg = malloc(sizeof(char) * (ft_strlen(minishell_cd) + \
	ft_strlen(string) + 1));
	if (!(msg))
		return ;
	i = 0;
	j = 0;
	while (minishell_cd && minishell_cd[j])
		msg[i++] = minishell_cd[j++];
	j = 0;
	while (string && string[j])
		msg[i++] = string[j++];
	msg[i] = '\0';
	perror(msg);
	free(msg);
}

void	cd_error_msg(const char *string, const char *error_msg)
{
	const char		*minishell_cd = "minishell: cd: ";
	char			*msg;
	unsigned int	i;
	unsigned int	j;

	msg = malloc(sizeof(char) * (ft_strlen(minishell_cd) + \
	ft_strlen(string) + ft_strlen(error_msg) + 2));
	if (!(msg))
		return ;
	i = 0;
	j = 0;
	while (minishell_cd && minishell_cd[j])
		msg[i++] = minishell_cd[j++];
	j = 0;
	while (string && string[j])
		msg[i++] = string[j++];
	j = 0;
	while (error_msg && error_msg[j])
		msg[i++] = error_msg[j++];
	msg[i++] = '\n';
	msg[i] = '\0';
	write(STDERR_FILENO, msg, ft_strlen(msg));
	free(msg);
}
