/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:48:08 by spayeur           #+#    #+#             */
/*   Updated: 2022/01/20 16:41:18 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	int		find;

	if (ft_strlen(little) == 0)
		return ((char *)big);
	find = 0;
	i = 0;
	while (i <= ft_strlen(big) - ft_strlen(little) \
	&& i + ft_strlen(little) <= len && find == 0)
	{
		find = 1;
		j = 0;
		while (j < ft_strlen(little))
		{
			if (big[i + j] != little[j])
				find = 0;
			j++;
		}
		i++;
	}
	if (find == 0)
		return (NULL);
	else
		return ((char *)(big + --i));
}
