/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 17:05:13 by rhullen           #+#    #+#             */
/*   Updated: 2020/06/27 17:05:45 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*get_digits(const char *format, int *dest)
{
	*dest = ft_atoi(format);
	while (ft_isdigit(*format))
		format++;
	return (--format);
}

const char	*get_precision(const char *format, va_list arg, t_flags *flags)
{
	if (*(++format) == '*')
	{
		if ((flags->precision = va_arg(arg, int)) >= 0)
			flags->is_precision = 1;
	}
	else
	{
		format = get_digits(format, &flags->precision);
		if (flags->precision >= 0)
			flags->is_precision = 1;
	}
	return (format);
}

const char	*parse_flags(const char *format, va_list arg, t_flags *flags)
{
	while (!ft_strchr(TYPES, *format))
	{
		if (*format == '-')
			flags->left_align = 1;
		else if (*format == '0')
			flags->add_zeros = 1;
		else if (ft_isdigit(*format) || *format == '*')
		{
			if (*format == '*')
			{
				if ((flags->width = va_arg(arg, int)) < 0)
				{
					flags->width *= -1;
					flags->left_align = 1;
				}
			}
			else
				format = get_digits(format, &flags->width);
		}
		else if (*format == '.')
			format = get_precision(format, arg, flags);
		format++;
	}
	return (format);
}
