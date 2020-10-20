/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:02:14 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/20 19:50:27 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_spaces_str(int size)
{
	char	*spaces;

	spaces = (char *)malloc(sizeof(char) * (size + 1));
	if (!spaces)
		return (0);
	spaces[size--] = '\0';
	while (size >= 0)
		spaces[size--] = 32;
	return (spaces);
}

char	*get_zeros_str(int len)
{
	char	*zeros;

	zeros = (char *)malloc(sizeof(char) * (len + 1));
	if (!zeros)
		return (0);
	zeros[len--] = '\0';
	while (len >= 0)
		zeros[len--] = '0';
	return (zeros);
}

char	*add_zeros(char *str, int total_len, int *nbr_len)
{
	char	*res;
	int		i;
	int		zeros_len;

	i = 0;
	if (*str == '-')
	{
		total_len += 1;
		i = 1;
		str++;
	}
	res = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!res)
		return (NULL);
	res[total_len] = '\0';
	if (i)
		res[0] = '-';
	zeros_len = total_len - *nbr_len;
	while (zeros_len--)
		res[i++] = '0';
	while (*str)
		res[i++] = *str++;
	free(str - *nbr_len);
	*nbr_len = total_len;
	return (res);
}

int		check_arg_s(va_list arg, t_flags *flags, int fd)
{
	char	*str;

	if (!(str = va_arg(arg, char *)))
		str = "(null)";
	return (print_s(str, flags, fd));
}

int		check_arg_p(va_list arg, t_flags *flags, int fd)
{
	unsigned long	ptr;

	if (!(ptr = va_arg(arg, unsigned long)))
		return (print_p(ft_strdup("(nil)"), flags, fd));
	else
		return (print_p(to_hex(ptr, 'x'), flags, fd));
}
