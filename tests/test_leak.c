/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_leak.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 16:44:08 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/25 16:48:56 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int		main(void)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		write(1, "child\n", 6);
		exit(0);
	}
	else
		write(1, "parent\n", 7);
	return (0);
}
