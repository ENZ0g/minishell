/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tohex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 17:48:14 by rhullen           #+#    #+#             */
/*   Updated: 2020/06/26 17:50:31 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_hex_length(unsigned long n)
{
	int len;

	len = 1;
	while (n / 16)
	{
		len++;
		n /= 16;
	}
	return (len);
}

char		*to_hex(unsigned long n, char mode)
{
	char	*symbols;
	char	*res;
	int		len;

	if (mode == 'x')
		symbols = HEX_LOW;
	else
		symbols = HEX_UPP;
	len = get_hex_length(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len--] = '\0';
	while (len >= 0)
	{
		res[len--] = symbols[n % 16];
		n /= 16;
	}
	return (res);
}
