/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:23:04 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/20 19:16:24 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf_error(const char *format, ...)
{
	va_list	arg;
	int		len;

	va_start(arg, format);
	len = handle_format_string(2, format, arg);
	va_end(arg);
	return (len);
}
