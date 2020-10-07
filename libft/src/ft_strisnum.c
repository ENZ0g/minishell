/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 00:59:47 by rhullen           #+#    #+#             */
/*   Updated: 2020/08/19 00:59:53 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strisnum(char *str)
{
	if (ft_isdigit(*str) || ft_strchr("-+", *str))
	{
		str++;
		while (*str)
		{
			if (ft_isdigit(*str))
				str++;
			else
				return (0);
		}
	}
	else
		return (0);
	return (1);
}
