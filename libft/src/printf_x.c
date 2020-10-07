/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:09:23 by rhullen           #+#    #+#             */
/*   Updated: 2020/06/26 13:50:31 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_x_spaces(char *hex, int len_spaces)
{
	ft_putstr_free(hex);
	ft_putstr_free(get_spaces_str(len_spaces));
}

static void	print_zeros_x(char *hex, int len_zeros)
{
	ft_putstr_free(get_zeros_str(len_zeros));
	ft_putstr_free(hex);
}

static void	print_spaces_x(char *hex, int len_spaces)
{
	ft_putstr_free(get_spaces_str(len_spaces));
	ft_putstr_free(hex);
}

int			print_x(char *hex, t_flags *flags)
{
	int		len;

	len = ft_strlen(hex);
	if (flags->is_precision && flags->precision == 0 &&
			!ft_strncmp(hex, "0", len))
		hex = empty_str(hex, &len);
	if (len < flags->precision)
		hex = add_zeros(hex, flags->precision, &len);
	if (len >= flags->width)
	{
		ft_putstr_free(hex);
		return (len);
	}
	if (flags->left_align)
	{
		print_x_spaces(hex, flags->width - len);
		return (flags->width);
	}
	if (flags->add_zeros && !flags->is_precision)
	{
		print_zeros_x(hex, flags->width - len);
		return (flags->width);
	}
	print_spaces_x(hex, flags->width - len);
	return (flags->width);
}
