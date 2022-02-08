/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_canonical_form.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:27:01 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/07 11:00:12 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*cut_substr(char *cd_string_allocated, char *target, unsigned int n)
{
	char			*new_string;
	unsigned int	i;
	unsigned int	j;

	if (!(cd_string_allocated))
		return (NULL);
	if (ft_strlen(target) < n)
		n = ft_strlen(target);
	new_string = malloc(sizeof(char) * \
	(ft_strlen(cd_string_allocated) - n + 1));
	if (!(new_string))
		return (cd_string_allocated);
	i = 0;
	j = 0;
	while (cd_string_allocated[i] && &cd_string_allocated[i] != target)
		new_string[j++] = cd_string_allocated[i++];
	while (cd_string_allocated[i] && &cd_string_allocated[i] != &target[n])
		i++;
	while (cd_string_allocated[i])
		new_string[j++] = cd_string_allocated[i++];
	new_string[j] = '\0';
	if (cd_string_allocated)
		free(cd_string_allocated);
	return (new_string);
}

int	canonical_form(const char *cd_string, char *cd_string_allocated, \
	char ***envp, const int outfile)
{
	cd_string_allocated = dot_slash(cd_string_allocated);
	cd_string_allocated = dot_dot_slash(cd_string, cd_string_allocated);
	if (!(cd_string_allocated))
		return (1);
	cd_string_allocated = slash_slash(cd_string_allocated);
	return (change_directory(cd_string, cd_string_allocated, envp, outfile));
}
