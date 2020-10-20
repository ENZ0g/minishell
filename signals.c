/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:41:49 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/20 21:37:18 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		quit_handler(int signum)
{
	int			exit_status;

	if ((exit_status = wait_for_process(shell)) == -1)
		return ;
	else if (exit_status == 131)
		write(2, "Quit: 3\n", 8);
	(void)signum;
}

static void		int_handler(int signum)
{
	int			exit_status;

	if ((exit_status = wait_for_process(shell)) == -1 && \
			shell->sigint_flag != 2)
	{
		ft_printf("\n");
		print_prompt();
		shell->sigint_flag = 1;
	}
	else if (exit_status == 130)
	{
		ft_printf("\n");
		shell->sigint_flag = 0;
	}
	else
		shell->sigint_flag = 2;
	(void)signum;
}

void			set_signals_handlers(void)
{
	signal(SIGQUIT, quit_handler);
	signal(SIGINT, int_handler);
}
