/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_utils_str2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:20:29 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/02 23:45:02 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	str_cmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	str_n_cmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
