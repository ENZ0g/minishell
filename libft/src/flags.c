/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 00:57:51 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/26 12:56:05 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_flags	*new_t_flags(void)
{
	t_flags	*flags;

	flags = (t_flags *)malloc(sizeof(t_flags));
	if (flags)
	{
		flags->left_align = 0;
		flags->add_zeros = 0;
		flags->width = 0;
		flags->is_precision = 0;
		flags->precision = 0;
		return (flags);
	}
	else
		return (NULL);
}

void	reset_flags(t_flags *flags)
{
	flags->left_align = 0;
	flags->add_zeros = 0;
	flags->width = 0;
	flags->is_precision = 0;
	flags->precision = 0;
}
