/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 13:23:57 by rhullen           #+#    #+#             */
/*   Updated: 2020/05/09 21:59:44 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int c)
{
	char	*temp;
	char	*result;

	result = 0;
	temp = (char *)str;
	while (*temp)
	{
		if (*temp == c)
			result = temp;
		temp++;
	}
	if (result)
		return (result);
	if (c == '\0')
		return (temp);
	return (0);
}
