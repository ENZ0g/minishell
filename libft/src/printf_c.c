/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:06:25 by rhullen           #+#    #+#             */
/*   Updated: 2020/06/26 13:28:51 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		print_c(unsigned char c, t_flags *flags)
{
	int		counter;
	char	*spaces;

	counter = 1;
	spaces = NULL;
	if (flags->width > 1)
	{
		counter = flags->width;
		spaces = get_spaces_str(flags->width - 1);
	}
	if (flags->left_align)
	{
		ft_putchar_fd(c, 1);
		if (spaces)
			ft_putstr_free(spaces);
	}
	else
	{
		if (spaces)
			ft_putstr_free(spaces);
		ft_putchar_fd(c, 1);
	}
	return (counter);
}
