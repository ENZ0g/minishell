/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endwith.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 00:03:53 by rhullen           #+#    #+#             */
/*   Updated: 2020/08/14 00:04:17 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_endwith(char *str, char *suffix)
{
	int suffix_len;
	int str_len;

	suffix_len = ft_strlen(suffix);
	str_len = ft_strlen(str);
	if (str_len >= suffix_len)
		return (ft_strcmp(str + str_len - suffix_len, suffix));
	return (0);
}
