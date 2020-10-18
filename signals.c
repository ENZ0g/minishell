/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:41:49 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/19 01:08:53 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	sigpipe_handler(int signum)
// {
// 	write(2, "hi\n", 3);
// 	exit(0);
// 	(void)signum;
// }

void	quit_handler(int signum)
{
	write(1, "\b\b  \b\b", 6);
	(void)signum;
}

void	int_handler(int signum)
{
	write(1, "\b\b  \b\b", 6);
	ft_printf("\n");
	print_prompt();
	shell->sigint_flag = 1;
	(void)signum;
}

void	set_signals_handlers(void)
{
	signal(SIGQUIT, quit_handler);
	signal(SIGINT, int_handler);
}
