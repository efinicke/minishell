/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_slash_or_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:22:43 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/03 17:20:23 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	cannot_access_parent_directories_msg(void)
{	
	perror("chdir: error retrieving current directory: getcwd: \
cannot access parent directories");
	return (1);
}

static char	*concatenate(const char *s1, char *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!(str))
		return (s2);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] && s2[j] != ':')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	if (s2)
		free(s2);
	return (str);
}

int	slash_or_pwd(const char *cd_string, char *cd_string_allocated, \
	char ***envp, const int outfile)
{
	const char	*pwd = pwd_accessors("GET", NULL);

	if (!(cd_string_allocated))
	{
		cd_string_allocated = malloc(sizeof(char) * (ft_strlen(cd_string) + 1));
		if (!(cd_string_allocated))
			return (EXIT_FAILURE);
		ft_strlcpy(cd_string_allocated, cd_string, (ft_strlen(cd_string) + 1));
	}
	if (cd_string_allocated[0] && cd_string_allocated[0] == '/')
		return (canonical_form(cd_string, cd_string_allocated, envp, outfile));
	if (!(pwd))
	{
		cannot_access_parent_directories_msg();
		free(cd_string_allocated);
		return (1);
	}
	if (pwd[ft_strlen(pwd) - 1] != '/')
		cd_string_allocated = concatenate("/", cd_string_allocated);
	cd_string_allocated = concatenate(pwd, cd_string_allocated);
	return (canonical_form(cd_string, cd_string_allocated, envp, outfile));
}
