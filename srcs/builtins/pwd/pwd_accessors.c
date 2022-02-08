/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_accessors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:41:42 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/03 17:01:21 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*retrieve_pwd(void)
{
	char	*pwd;
	size_t	size;

	size = 2;
	pwd = malloc(sizeof(char) * size);
	if (!(pwd))
		return (NULL);
	while (getcwd(pwd, size) == NULL)
	{
		if (pwd)
			free(pwd);
		if (errno != 34)
			return (NULL);
		size *= 2;
		pwd = malloc(sizeof(char) * size);
		if (!(pwd))
			return (NULL);
	}
	return (pwd);
}

static char	*pwd_get(char *pwd)
{
	DIR		*dir;
	char	*retrieved_pwd;

	if (pwd)
	{
		dir = opendir(pwd);
		if (dir)
		{
			closedir(dir);
			return (pwd);
		}
		free(pwd);
	}
	retrieved_pwd = retrieve_pwd();
	return (retrieved_pwd);
}

static char	*pwd_replace(char *pwd, char *value)
{
	char	*value_allocated;

	if (value)
	{
		value_allocated = malloc(sizeof(char) * (ft_strlen(value) + 1));
		if (!(value_allocated))
			return (NULL);
		ft_strlcpy(value_allocated, value, (ft_strlen(value) + 1));
		free(pwd);
		return (value_allocated);
	}
	else
	{
		free(pwd);
		return (value);
	}
}

static char	*pwd_set(char *value)
{
	char	*value_allocated;

	if (value)
	{
		value_allocated = malloc(sizeof(char) * (ft_strlen(value) + 1));
		if (!(value_allocated))
			return (NULL);
		ft_strlcpy(value_allocated, value, (ft_strlen(value) + 1));
		return (value_allocated);
	}
	else
	{
		return (value);
	}
}

const char	*pwd_accessors(const char *accessor, char *value)
{
	static char	*pwd = NULL;

	if (ft_strlen(accessor) == 3)
	{
		if (ft_strncmp(accessor, "GET", 3) == 0)
		{
			pwd = pwd_get(pwd);
			return (pwd);
		}
		else if (ft_strncmp(accessor, "SET", 3) == 0)
		{
			if (pwd)
			{
				pwd = pwd_replace(pwd, value);
				return (pwd);
			}
			else
			{
				pwd = pwd_set(value);
				return (pwd);
			}
		}
	}
	return (NULL);
}
