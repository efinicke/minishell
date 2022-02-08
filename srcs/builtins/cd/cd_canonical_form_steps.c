/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_canonical_form_steps.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:30:21 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/07 11:19:20 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*dot_slash(char *str_allocated)
{
	char	*ds;

	ds = ft_strnstr(str_allocated, "/./", ft_strlen(str_allocated));
	while (ds)
	{
		str_allocated = cut_substr(str_allocated, &ds[1], 2);
		ds = ft_strnstr(str_allocated, "/./", ft_strlen(str_allocated));
	}
	if (ft_strlen(str_allocated) > 1 \
	&& str_allocated[ft_strlen(str_allocated) - 1] == '.' \
	&& str_allocated[ft_strlen(str_allocated) - 2] == '/')
	{
		str_allocated = cut_substr(str_allocated, \
		&str_allocated[ft_strlen(str_allocated) - 1], 1);
	}
	return (str_allocated);
}

static char	*dot_dot_slash_check_preceding_component(const char *str, \
		char *str_allocated, char *dds)
{
	DIR		*dir;
	char	*component;
	int		i;

	i = 0;
	while (str_allocated != (dds + i) && *(dds + i) == '/')
		i--;
	i++;
	component = malloc(sizeof(char) * ((dds + i) - (str_allocated) + 1));
	if (!(component))
	{
		free(str_allocated);
		return (NULL);
	}
	ft_strlcpy(component, str_allocated, ((dds + i) - (str_allocated) + 1));
	dir = opendir(component);
	free(component);
	if (!(dir))
	{
		free(str_allocated);
		cd_perror_msg(str);
		return (NULL);
	}
	closedir(dir);
	return (str_allocated);
}

static char	*dot_dot_slash_cut(char *str_allocated, char *dds)
{
	int				i;
	unsigned int	j;

	i = 0;
	while (str_allocated != (dds + i) && *(dds + i) == '/')
		i--;
	while (str_allocated != (dds + i) && *(dds + i) != '/')
		i--;
	i++;
	j = 1;
	while (dds[j] && dds[j] != '/')
		j++;
	while (dds[j] && dds[j] == '/')
		j++;
	str_allocated = cut_substr(str_allocated, (dds + i), \
	((dds + j) - (dds + i)));
	return (str_allocated);
}

char	*dot_dot_slash(const char *str, char *str_allocated)
{
	char	*dds;

	dds = ft_strnstr(str_allocated, "/../", ft_strlen(str_allocated));
	while (dds)
	{
		str_allocated = dot_dot_slash_check_preceding_component(str, \
		str_allocated, dds);
		if (!(str_allocated))
			return (NULL);
		str_allocated = dot_dot_slash_cut(str_allocated, dds);
		dds = ft_strnstr(str_allocated, "/../", ft_strlen(str_allocated));
	}
	if (ft_strlen(str_allocated) > 2 \
	&& str_allocated[ft_strlen(str_allocated) - 1] == '.' \
	&& str_allocated[ft_strlen(str_allocated) - 2] == '.' \
	&& str_allocated[ft_strlen(str_allocated) - 3] == '/')
	{
		str_allocated = dot_dot_slash_check_preceding_component(str, \
		str_allocated, &str_allocated[ft_strlen(str_allocated) - 3]);
		if (!(str_allocated))
			return (NULL);
		str_allocated = dot_dot_slash_cut(str_allocated, \
		&str_allocated[ft_strlen(str_allocated) - 3]);
	}
	return (str_allocated);
}

char	*slash_slash(char *str_allocated)
{
	char			*ss;
	unsigned int	i;

	i = 0;
	while (str_allocated[i] && str_allocated[i] == '/')
		i++;
	if (i > 2)
		str_allocated = cut_substr(str_allocated, str_allocated + 1, (i - 1));
	ss = ft_strnstr(str_allocated + 1, "//", ft_strlen(str_allocated));
	while (ss)
	{
		i = 0;
		while (ss[i] && ss[i] == '/')
			i++;
		str_allocated = cut_substr(str_allocated, (ss + 1), (i - 1));
		ss = ft_strnstr(str_allocated + 1, "//", ft_strlen(str_allocated));
	}
	if (ft_strlen(str_allocated) > 2 \
	&& str_allocated[ft_strlen(str_allocated) - 1] == '/')
		str_allocated = cut_substr(str_allocated, \
		(str_allocated + (ft_strlen(str_allocated) - 1)), 1);
	return (str_allocated);
}
