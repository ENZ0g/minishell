/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 23:42:52 by rhullen           #+#    #+#             */
/*   Updated: 2020/05/09 21:47:24 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*ptr;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (s_len < start)
		return ((char *)ft_calloc(1, 1));
	s_len = ft_strlen(s + start);
	if (s_len < len)
		len = s_len;
	ptr = (char *)malloc(len * sizeof(char) + 1);
	if (ptr)
		ft_strlcpy(ptr, s + start, len * sizeof(char) + 1);
	return (ptr);
}
