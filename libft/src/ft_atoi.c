/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 00:17:14 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/20 17:11:40 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
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
	while (ft_isspace(*nptr))
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
