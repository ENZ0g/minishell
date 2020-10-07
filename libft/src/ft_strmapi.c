/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 17:02:07 by rhullen           #+#    #+#             */
/*   Updated: 2020/05/09 23:09:30 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (!(s && f))
		return (0);
	result = ft_strdup(s);
	if (result)
	{
		i = 0;
		while (result[i])
		{
			result[i] = f(i, result[i]);
			i++;
		}
	}
	return (result);
}
