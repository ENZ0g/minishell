/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:41:49 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/09 20:27:56 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	(void)signum;
}

void	set_signals_handlers(void)
{
	signal(SIGQUIT, quit_handler);
	signal(SIGINT, int_handler);
}