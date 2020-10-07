/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 17:07:56 by rhullen           #+#    #+#             */
/*   Updated: 2020/05/11 13:12:41 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t counter;

	if (!(dst && src))
		return (0);
	counter = 0;
	while (size > 1 && *src)
	{
		*dst++ = *src++;
		counter++;
		size--;
	}
	if (counter || !*src)
		*dst = '\0';
	if (*src)
		return (ft_strlen(src - counter));
	return (counter);
}
