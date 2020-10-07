/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 18:20:58 by rhullen           #+#    #+#             */
/*   Updated: 2020/05/09 21:37:57 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	counter;

	counter = 0;
	if (!(dst && src))
		return (0);
	while (*dst && size)
	{
		dst++;
		size--;
		counter++;
	}
	if (size-- == 0)
		return (counter + ft_strlen(src));
	while (*src)
	{
		if (size > 0)
		{
			size--;
			*dst++ = *src;
		}
		src++;
		counter++;
	}
	*dst = '\0';
	return (counter);
}
