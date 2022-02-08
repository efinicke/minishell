/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_utils_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:20:18 by efinicke          #+#    #+#             */
/*   Updated: 2022/02/02 23:44:40 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_dup(char *s1)
{
	char	*s2;
	char	*stmp;

	if (!s1)
		return (NULL);
	s2 = malloc(sizeof(*s1) * (str_len(s1) + 1));
	if (!s2)
		return (NULL);
	stmp = s2;
	while (*s1)
		*s2++ = *s1++;
	*s2 = '\0';
	return (stmp);
}

int	str_len(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i])
		i++;
	return (i);
}

static void	sub_strjoin(char *cmd, char *s1, char *c)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		cmd[i] = s1[i];
		i++;
	}
	while (c && c[j])
	{
		cmd[i + j] = c[j];
		j++;
	}
	cmd[i + j] = '\0';
}

char	*strjoin_free(char *s1, char *c)
{
	char	*cmd;
	int		len;

	len = str_len(s1) + str_len(c);
	cmd = malloc(sizeof(char) * (len + 1));
	if (!cmd)
		return (NULL);
	sub_strjoin(cmd, s1, c);
	if (s1)
		free(s1);
	if (c)
		free(c);
	return (cmd);
}

char	*str_c_join(char *s1, char c)
{
	char	*cc;

	if (c)
	{
		cc = malloc(sizeof(char) * 2);
		if (!cc)
			return (NULL);
		cc[0] = c;
		cc[1] = '\0';
		s1 = strjoin_free(s1, cc);
	}
	if (s1)
		return (s1);
	return (NULL);
}
