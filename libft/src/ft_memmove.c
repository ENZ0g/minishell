/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 14:04:58 by rhullen           #+#    #+#             */
/*   Updated: 2020/05/10 22:22:50 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	if (!(dest && src))
		return (0);
	tmp1 = dest;
	tmp2 = (unsigned char *)src;
	if (tmp1 > tmp2)
	{
		while (n--)
			*(tmp1 + n) = *(tmp2 + n);
	}
	else if (tmp1 < tmp2)
	{
		while (n--)
			*tmp1++ = *tmp2++;
	}
	return (dest);
}
