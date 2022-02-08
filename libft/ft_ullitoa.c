/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ullitoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:48:57 by spayeur           #+#    #+#             */
/*   Updated: 2022/01/31 14:05:17 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nblen(unsigned long long int n)
{
	unsigned int	i;

	i = 0;
	if (n >= 10)
		i = ft_nblen(n / 10);
	return (++i);
}

static void	ft_putnbstr(char *s, unsigned long long int n, unsigned int *addr_i)
{
	if (n >= 10)
		ft_putnbstr(s, n / 10, addr_i);
	s[*addr_i] = n % 10 + '0';
	*addr_i = *addr_i + 1;
}

char	*ft_ullitoa(unsigned long long int n)
{
	char			*s;
	unsigned int	i;

	s = malloc((ft_nblen(n) + 1));
	if (!(s))
		return (NULL);
	s[ft_nblen(n)] = '\0';
	i = 0;
	ft_putnbstr(s, n, &i);
	return (s);
}
