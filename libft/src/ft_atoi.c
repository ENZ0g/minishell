/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 00:17:14 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/24 14:22:44 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(int c)
{
	return ((c > 8 && c < 14) || c == 32);
}

int			ft_atoi(const char *nptr)
{
	int	sign;
	int	result;

	if (nptr == NULL)
		return (0);
	sign = 1;
	result = 0;
	while (is_space(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		sign *= 44 - *nptr;
		nptr++;
	}
	if (*nptr >= '0' && *nptr <= '9')
	{
		while (*nptr >= '0' && *nptr <= '9')
		{
			result = result * 10 + (*nptr - '0');
			nptr++;
		}
		return (result * sign);
	}
	return (0);
}
