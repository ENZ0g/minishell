/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_di.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:07:51 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/20 19:50:54 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*empty_str(char *str, int *len)
{
	*len = 0;
	free(str);
	return (ft_strdup(""));
}

static void	print_zeros_di(char *nbr, int len_zeros, int fd)
{
	int minus;

	minus = 0;
	if (*nbr == '-')
	{
		ft_putchar_fd('-', fd);
		minus = 1;
	}
	ft_putstr_free(get_zeros_str(len_zeros), fd);
	ft_putstr_fd(nbr + minus, fd);
	free(nbr);
}

static void	print_di_spaces(char *nbr, int len_spaces, int fd)
{
	ft_putstr_free(nbr, fd);
	ft_putstr_free(get_spaces_str(len_spaces), fd);
}

static void	print_spaces_di(char *nbr, int len_spaces, int fd)
{
	ft_putstr_free(get_spaces_str(len_spaces), fd);
	ft_putstr_free(nbr, fd);
}

int			print_di(char *nbr, t_flags *flags, int fd)
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
		ft_putstr_free(nbr, fd);
		return (len);
	}
	if (flags->left_align)
	{
		print_di_spaces(nbr, flags->width - len, fd);
		return (flags->width);
	}
	if (flags->add_zeros && !flags->is_precision)
	{
		print_zeros_di(nbr, flags->width - len, fd);
		return (flags->width);
	}
	print_spaces_di(nbr, flags->width - len, fd);
	return (flags->width);
}
