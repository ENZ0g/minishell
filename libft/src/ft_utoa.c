/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 17:06:20 by rhullen           #+#    #+#             */
/*   Updated: 2020/06/26 17:07:26 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_dec_length(unsigned int n)
{
	int	len;

	len = 1;
	while (n /= 10)
		len++;
	return (len);
}

char		*ft_utoa(unsigned int n)
{
	int		len;
	char	*res;

	len = get_dec_length(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len--] = '\0';
	while (len >= 0)
	{
		res[len--] = '0' + n % 10;
		n /= 10;
	}
	return (res);
}
