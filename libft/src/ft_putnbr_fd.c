/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 20:45:55 by rhullen           #+#    #+#             */
/*   Updated: 2020/05/11 23:59:53 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			tmp;
	unsigned int	uns_n;

	if (n < 0)
	{
		write(fd, "-", 1);
		uns_n = n * -1;
	}
	else
		uns_n = n;
	if (uns_n / 10 == 0)
	{
		tmp = '0' + uns_n;
		write(fd, &tmp, 1);
	}
	else
	{
		ft_putnbr_fd(uns_n / 10, fd);
		ft_putnbr_fd(uns_n % 10, fd);
	}
}
