/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 12:15:07 by rhullen           #+#    #+#             */
/*   Updated: 2020/05/10 22:19:47 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;
	unsigned char	stop;

	tmp1 = (unsigned char *)dest;
	tmp2 = (unsigned char *)src;
	stop = (unsigned char)c;
	if (!(dest && src))
		return (0);
	while (n--)
	{
		*tmp1 = *tmp2;
		if (*tmp2 == stop)
			return (++tmp1);
		tmp1++;
		tmp2++;
	}
	return (0);
}
