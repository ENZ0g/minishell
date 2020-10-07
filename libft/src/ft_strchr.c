/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 12:59:25 by rhullen           #+#    #+#             */
/*   Updated: 2020/05/10 23:01:28 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	char	*temp;

	if (!str)
		return (0);
	temp = (char *)str;
	while (*temp)
	{
		if (*temp == c)
			return (temp);
		temp++;
	}
	if (c == '\0')
		return (temp);
	return (0);
}
