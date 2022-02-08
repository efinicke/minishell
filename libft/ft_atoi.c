/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <spayeur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:41:47 by spayeur           #+#    #+#             */
/*   Updated: 2022/02/07 13:29:57 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	i = 0;
	if (!(nptr))
		return (0);
	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n' \
	|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		nb *= 10;
		nb += nptr[i] - '0';
		i++;
	}
	return (nb * sign);
}
