/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:06:55 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/20 19:39:09 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_s_spaces(char *str, int len, char *spaces, int fd)
{
	ft_putstrn(str, len, fd);
	if (spaces)
		ft_putstr_free(spaces, fd);
}

static void	print_spaces_s(char *str, int len, char *spaces, int fd)
{
	if (spaces)
		ft_putstr_free(spaces, fd);
	ft_putstrn(str, len, fd);
}

int			print_s(char *str, t_flags *flags, int fd)
{
	int		len;
	char	*spaces;
	int		counter;

	spaces = NULL;
	len = ft_strlen(str);
	if (flags->is_precision && !ft_strncmp("(null)", str, 6) &&
			flags->precision < 6)
	{
		str = "";
		len = 0;
	}
	if (flags->is_precision && flags->precision < len)
		len = flags->precision;
	counter = len;
	if (len < flags->width)
	{
		counter = flags->width;
		spaces = get_spaces_str(flags->width - len);
	}
	if (flags->left_align)
		print_s_spaces(str, len, spaces, fd);
	else
		print_spaces_s(str, len, spaces, fd);
	return (counter);
}
