/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:08:53 by rhullen           #+#    #+#             */
/*   Updated: 2020/06/26 13:33:56 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_hex(char *hex, int prefix)
{
	if (prefix)
		ft_putstr_fd("0x", 1);
	ft_putstr_free(hex);
}

static void	print_hex_spaces(char *hex, int prefix, int len)
{
	if (prefix)
		ft_putstr_fd("0x", 1);
	ft_putstr_free(hex);
	ft_putstr_free(get_spaces_str(len));
}

static void	print_spaces_hex(char *hex, int prefix, int len)
{
	ft_putstr_free(get_spaces_str(len));
	if (prefix)
		ft_putstr_fd("0x", 1);
	ft_putstr_free(hex);
}

static void	print_zeros_hex(char *hex, int prefix, int len)
{
	if (prefix)
		ft_putstr_fd("0x", 1);
	ft_putstr_free(get_zeros_str(len));
	ft_putstr_free(hex);
}

int			print_p(char *hex, t_flags *flags)
{
	int		len;
	int		prefix;

	prefix = (ft_strncmp("(nil)", hex, 5) == 0) ? 0 : 2;
	len = ft_strlen(hex);
	if (len < flags->precision)
		hex = add_zeros(hex, flags->precision, &len);
	if (len + prefix >= flags->width)
	{
		print_hex(hex, prefix);
		return (len + prefix);
	}
	if (flags->left_align)
	{
		print_hex_spaces(hex, prefix, flags->width - len - prefix);
		return (flags->width);
	}
	if (flags->add_zeros && !flags->is_precision)
	{
		print_zeros_hex(hex, prefix, flags->width - len - prefix);
		return (flags->width);
	}
	print_spaces_hex(hex, prefix, flags->width - len - prefix);
	return (flags->width);
}
