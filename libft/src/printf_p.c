/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:08:53 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/20 19:37:00 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_hex(char *hex, int prefix, int fd)
{
	if (prefix)
		ft_putstr_fd("0x", 1);
	ft_putstr_free(hex, fd);
}

static void	print_hex_spaces(char *hex, int prefix, int len, int fd)
{
	if (prefix)
		ft_putstr_fd("0x", fd);
	ft_putstr_free(hex, fd);
	ft_putstr_free(get_spaces_str(len), fd);
}

static void	print_spaces_hex(char *hex, int prefix, int len, int fd)
{
	ft_putstr_free(get_spaces_str(len), fd);
	if (prefix)
		ft_putstr_fd("0x", fd);
	ft_putstr_free(hex, fd);
}

static void	print_zeros_hex(char *hex, int prefix, int len, int fd)
{
	if (prefix)
		ft_putstr_fd("0x", fd);
	ft_putstr_free(get_zeros_str(len), fd);
	ft_putstr_free(hex, fd);
}

int			print_p(char *hex, t_flags *flags, int fd)
{
	int		len;
	int		prefix;

	prefix = (ft_strncmp("(nil)", hex, 5) == 0) ? 0 : 2;
	len = ft_strlen(hex);
	if (len < flags->precision)
		hex = add_zeros(hex, flags->precision, &len);
	if (len + prefix >= flags->width)
	{
		print_hex(hex, prefix, fd);
		return (len + prefix);
	}
	if (flags->left_align)
	{
		print_hex_spaces(hex, prefix, flags->width - len - prefix, fd);
		return (flags->width);
	}
	if (flags->add_zeros && !flags->is_precision)
	{
		print_zeros_hex(hex, prefix, flags->width - len - prefix, fd);
		return (flags->width);
	}
	print_spaces_hex(hex, prefix, flags->width - len - prefix, fd);
	return (flags->width);
}
