/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 13:49:41 by rhullen           #+#    #+#             */
/*   Updated: 2020/05/12 00:42:32 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_entirely(const char *str1, const char *str2, int n)
{
	while (*str1 && *str1 == *str2 && n > 0)
	{
		str1++;
		str2++;
		n--;
	}
	if (!*str2)
		return (1);
	return (0);
}

char		*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	if (*str2 == '\0')
		return ((char *)str1);
	while (*str1 && len > 0)
	{
		if (*str1 == *str2)
		{
			if (is_entirely(str1, str2, len))
				return ((char *)str1);
		}
		str1++;
		len--;
	}
	return (0);
}
