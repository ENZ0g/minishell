/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_di.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:07:51 by rhullen           #+#    #+#             */
/*   Updated: 2020/06/26 13:46:46 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*empty_str(char *str, int *len)
{
	*len = 0;
	free(str);
	return (ft_strdup(""));
}

static void	print_zeros_di(char *nbr, int len_zeros)
{
	int minus;

	minus = 0;
	if (*nbr == '-')
	{
		ft_putchar_fd('-', 1);
		minus = 1;
	}
	ft_putstr_free(get_zeros_str(len_zeros));
	ft_putstr_fd(nbr + minus, 1);
	free(nbr);
}

static void	print_di_spaces(char *nbr, int len_spaces)
{
	ft_putstr_free(nbr);
	ft_putstr_free(get_spaces_str(len_spaces));
}

static void	print_spaces_di(char *nbr, int len_spaces)
{
	ft_putstr_free(get_spaces_str(len_spaces));
	ft_putstr_free(nbr);
}

int			print_di(char *nbr, t_flags *flags)
{
	int	len;

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
		print_di_spaces(nbr, flags->width - len);
		return (flags->width);
	}
	if (flags->add_zeros && !flags->is_precision)
	{
		print_zeros_di(nbr, flags->width - len);
		return (flags->width);
	}
	print_spaces_di(nbr, flags->width - len);
	return (flags->width);
}
