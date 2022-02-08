/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:52:22 by spayeur           #+#    #+#             */
/*   Updated: 2021/05/31 02:59:45 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wc(const char *s, char sep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == sep)
			i++;
		else
		{
			while (s[i] && s[i] != sep)
				i++;
			j++;
		}
	}
	return (j);
}

static void	*ft_str_alloc_protect(char **tab, int j)
{
	while (j >= 0)
	{
		free(tab[j]);
		j--;
	}
	free(tab);
	return (NULL);
}

static void	*ft_str_alloc(const char *s, char sep, char **tab)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == sep)
			i++;
		else
		{
			k = 0;
			while (s[i] && s[i] != sep)
			{
				i++;
				k++;
			}
			tab[j] = malloc(sizeof(char) * (++k));
			if (!(tab[j]))
				return (ft_str_alloc_protect(tab, j));
			j++;
		}
	}
	return ((void *)1);
}

static void	ft_str_putstr(const char *s, char sep, char **tab)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == sep)
			i++;
		else
		{
			k = 0;
			while (s[i] && s[i] != sep)
			{
				tab[j][k] = s[i];
				i++;
				k++;
			}
			tab[j][k] = '\0';
			j++;
		}
	}
	tab[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(void *) * (ft_wc(s, c) + 1));
	if (!(tab))
		return (NULL);
	if (!(ft_str_alloc(s, c, tab)))
		return (NULL);
	ft_str_putstr(s, c, tab);
	return (tab);
}
