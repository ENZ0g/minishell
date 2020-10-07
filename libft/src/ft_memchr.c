/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 10:44:03 by rhullen           #+#    #+#             */
/*   Updated: 2020/05/10 20:01:15 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	unsigned char	to_find;

	tmp = (unsigned char *)s;
	to_find = c;
	while (n--)
	{
		if (*tmp == to_find)
			return (tmp);
		tmp++;
	}
	return (0);
}
