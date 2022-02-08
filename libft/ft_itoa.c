/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:26:34 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/07 13:27:40 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nblen(int n)
{
	int	i;

	i = 0;
	if (n >= 10)
		i = ft_nblen(n / 10);
	return (++i);
}

static void	ft_putnbstr(char *s, int neg, int n)
{
	static int	i;

	i = neg;
	if (n >= 10)
		ft_putnbstr(s, neg, n / 10);
	s[i++] = n % 10 + '0';
}

char	*ft_itoa(int n)
{
	int		neg;
	char	*s;

	if (n == -2147483648)
	{
		s = malloc(12);
		if (s == NULL)
			return (NULL);
		ft_strlcpy(s, "-2147483648", 12);
		return (s);
	}
	neg = 0;
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	s = malloc((ft_nblen(n) + neg + 1));
	if (s == NULL)
		return (NULL);
	if (neg)
		s[0] = '-';
	s[(ft_nblen(n) + neg)] = '\0';
	ft_putnbstr(s, neg, n);
	return (s);
}
