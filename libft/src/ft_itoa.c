/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 17:54:03 by rhullen           #+#    #+#             */
/*   Updated: 2020/05/12 00:00:50 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	unsigned int	tmp_n;
	char			*res;
	char			*tmp_s;
	int				sign;

	tmp_n = n;
	sign = 0;
	if (n < 0)
	{
		tmp_n = n * -1;
		sign = 1;
	}
	res = ft_utoa(tmp_n);
	if (sign)
	{
		tmp_s = res;
		res = ft_strjoin("-", res);
		free(tmp_s);
	}
	return (res);
}
