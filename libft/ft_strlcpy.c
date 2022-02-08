/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:24:32 by spayeur           #+#    #+#             */
/*   Updated: 2022/01/31 14:05:24 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t		i;

	if (!dest || !src)
		return (0);
	if (!(src[0]))
	{
		if (size != 0)
			dest[0] = src[0];
		return (0);
	}
	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && (i < size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	if (size != 0)
		dest[i] = '\0';
	return (ft_strlen(src));
}
