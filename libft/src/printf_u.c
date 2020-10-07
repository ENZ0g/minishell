/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:08:16 by rhullen           #+#    #+#             */
/*   Updated: 2020/06/26 13:30:24 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_u_spaces(char *nbr, int len_spaces)
{
	ft_putstr_free(nbr);
	ft_putstr_free(get_spaces_str(len_spaces));
}

static void	print_zeros_u(char *nbr, int len_zeros)
{
	ft_putstr_free(get_zeros_str(len_zeros));
	ft_putstr_free(nbr);
}

static void	print_spaces_u(char *nbr, int len_spaces)
{
	ft_putstr_free(get_spaces_str(len_spaces));
	ft_putstr_free(nbr);
}

int			print_u(char *nbr, t_flags *flags)
{
	int		len;

	len = ft_strlen(nbr);
	if (flags->is_precision && flags->precision == 0 &&
		!ft_strncmp(nbr, "0", len))
		nbr = empty_str(nbr, &len);
	if (len < flags->precision)
		nbr = add_zeros(nbr, flags->precision, &len);
	if (len >= flags->width)
	{
		ft_putstr_free(nbr);
		return (len);
	}
	if (flags->left_align)
	{
		print_u_spaces(nbr, flags->width - len);
		return (flags->width);
	}
	if (flags->add_zeros && !flags->is_precision)
	{
		print_zeros_u(nbr, flags->width - len);
		return (flags->width);
	}
	print_spaces_u(nbr, flags->width - len);
	return (flags->width);
}
