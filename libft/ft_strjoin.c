/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:12:10 by spayeur           #+#    #+#             */
/*   Updated: 2021/11/15 02:11:36 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		size1;
	int		size2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	str = malloc((size1 + size2 + 1) * sizeof(char));
	if (!(str))
		return (NULL);
	i = -1;
	while (++i < size1)
		str[i] = s1[i];
	i = -1;
	while (++i < size2)
		str[i + size1] = s2[i];
	str[i + size1] = '\0';
	return (str);
}
