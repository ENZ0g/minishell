/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:41:49 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/20 15:12:44 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	sigpipe_handler(int signum)
// {
// 	write(2, "hi\n", 3);
// 	exit(0);
// 	(void)signum;
// }

// void			child_quit_handler(int signum)
// {
// 	// write(2, "Quit: 3\n", 8);
// 	exit(3);
// 	(void)signum;
// }

static void		quit_handler(int signum)
{
	int			exit_status;

	if ((exit_status = wait_for_process(shell)) == -1)
		return ;
	else if (exit_status == 131)
		write(2, "Quit: 3\n", 8);
	// else
		// write(1, "\b\b  \b\b", 6);
	// shell->sigint_flag = 0;
	(void)signum;
}

static void		int_handler(int signum)
{
	int			exit_status;

	if ((exit_status = wait_for_process(shell)) == -1 && shell->sigint_flag != 2)
	{
		// write(1, "\b\b  \b\b", 6);
		ft_printf("\n");
		print_prompt();
		shell->sigint_flag = 1;
	}
	// if (!shell->tokens)
	else if (exit_status == 130)
	{
		ft_printf("\n");
		shell->sigint_flag = 0;
	}
	else
		shell->sigint_flag = 2;
	// if (!shell->child_pid_count)
	// {

	// }
	// else
	// {
	// 	// write(1, "\b\b  \b\b", 6);

	// }
	
	(void)signum;
}

void			set_signals_handlers(void)
{
	signal(SIGQUIT, quit_handler);
	signal(SIGINT, int_handler);
}
