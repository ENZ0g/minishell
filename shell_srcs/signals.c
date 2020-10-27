/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:41:49 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/25 14:59:02 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		quit_handler(int signum)
{
	int			exit_status;

	if ((exit_status = wait_for_process()) == -1)
		return ;
	else if (exit_status == 131)
		write(2, "Quit: 3\n", 8);
	(void)signum;
}

static void		int_handler(int signum)
{
	int			exit_status;

	if ((exit_status = wait_for_process()) == -1 && g_sigint_flag != 2)
	{
		ft_printf("\n");
		print_prompt();
		g_sigint_flag = 1;
		errno = 0;
	}
	else if (exit_status == 130)
	{
		ft_printf("\n");
		g_sigint_flag = 0;
	}
	else
		g_sigint_flag = 2;
	(void)signum;
}

void			set_signals_handlers(void)
{
	signal(SIGQUIT, quit_handler);
	signal(SIGINT, int_handler);
}
