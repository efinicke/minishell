/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cdpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:24:32 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/05 16:34:38 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*concatenate(char *s1, char const *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!(str))
		return (s1);
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
	if (s1)
		free(s1);
	return (str);
}

static int	dotslash_concatenate(const char *cd_string, char ***envp)
{
	DIR		*dir;
	char	*cdpath_allocated;

	cdpath_allocated = malloc(sizeof(char) * (1));
	if (!(cdpath_allocated))
		return (EXIT_FAILURE);
	cdpath_allocated[0] = '\0';
	cdpath_allocated = concatenate(cdpath_allocated, "./");
	cdpath_allocated = concatenate(cdpath_allocated, cd_string);
	dir = opendir(cdpath_allocated);
	if (dir)
	{
		closedir(dir);
		return (slash_or_pwd(cd_string, cdpath_allocated, envp, -1));
	}
	else
	{
		free(cdpath_allocated);
	}
	return (-1);
}

static char	*cdpath_concatenate(const char *cd_string, const char *cdpath, \
		unsigned int *addr_i)
{
	char			*cdpath_allocated;
	unsigned int	j;

	if (cdpath[*addr_i] && cdpath[*addr_i] == ':')
		*addr_i = *addr_i + 1;
	j = *addr_i;
	while (cdpath[j] && cdpath[j] != ':')
		j++;
	cdpath_allocated = malloc(sizeof(char) * (j - *addr_i + 1));
	if (!(cdpath_allocated))
		return (NULL);
	ft_strlcpy(cdpath_allocated, &cdpath[*addr_i], (j - *addr_i + 1));
	if (cdpath[j - 1] != '/')
		cdpath_allocated = concatenate(cdpath_allocated, "/");
	cdpath_allocated = concatenate(cdpath_allocated, cd_string);
	*addr_i = *addr_i + j;
	return (cdpath_allocated);
}

static int	check_all_cdpath(const char *cd_string, const char *cdpath, \
		char ***envp, const int outfile)
{
	char			*cdpath_allocated;
	DIR				*dir;
	unsigned int	i;

	i = 0;
	while (cdpath[i])
	{
		cdpath_allocated = cdpath_concatenate(cd_string, cdpath, &i);
		if (!(cdpath_allocated))
			return (EXIT_FAILURE);
		dir = opendir(cdpath_allocated);
		if (dir)
		{
			closedir(dir);
			return (slash_or_pwd(cd_string, cdpath_allocated, envp, outfile));
		}
		else
		{
			free(cdpath_allocated);
		}
	}
	return (-1);
}

int	cdpath(const char *cd_string, char ***envp, const int outfile)
{
	const char	*cdpath = ft_getenv("CDPATH", (const char **)*envp);
	int			ret;

	if (cdpath)
	{
		ret = check_all_cdpath(cd_string, cdpath, envp, outfile);
		if (ret != -1)
			return (ret);
	}
	ret = dotslash_concatenate(cd_string, envp);
	if (ret != -1)
		return (ret);
	return (slash_or_pwd(cd_string, NULL, envp, -1));
}
