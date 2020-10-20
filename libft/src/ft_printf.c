/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:58:39 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/20 19:50:03 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_conv(const char *format, va_list arg, t_flags *flags, int fd)
{
	int				counter;

	counter = 0;
	if (*format == '%')
		counter += ft_putchar_fd('%', 1);
	else if (*format == 'c')
		counter += print_c(va_arg(arg, int), flags, fd);
	else if (*format == 's')
		counter += check_arg_s(arg, flags, fd);
	else if (*format == 'd' || *format == 'i')
		counter += print_di(ft_itoa(va_arg(arg, int)), flags, fd);
	else if (*format == 'u')
		counter += print_u(ft_utoa(va_arg(arg, unsigned int)), flags, fd);
	else if (*format == 'x')
		counter += print_x(to_hex(va_arg(arg, unsigned int), 'x'), flags, fd);
	else if (*format == 'X')
		counter += print_x(to_hex(va_arg(arg, unsigned int), 'X'), flags, fd);
	else if (*format == 'p')
		counter += check_arg_p(arg, flags, fd);
	return (counter);
}

int			handle_format_string(int fd, const char *format, va_list arg)
{
	int		counter;
	t_flags	*flags;

	counter = 0;
	flags = new_t_flags();
	while (*format)
	{
		if (*format == '%')
		{
			if (*(format + 1) == '\0')
			{
				free(flags);
				flags = NULL;
				return (-1);
			}
			format = parse_flags(++format, arg, flags);
			counter += handle_conv(format++, arg, flags, fd);
			reset_flags(flags);
		}
		else
			counter += ft_putchar_fd(*format++, fd);
	}
	free(flags);
	flags = NULL;
	return (counter);
}

int			ft_printf(const char *format, ...)
{
	va_list	arg;
	int		len;

	va_start(arg, format);
	len = handle_format_string(1, format, arg);
	va_end(arg);
	return (len);
}
