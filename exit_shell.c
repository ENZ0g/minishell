/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:10:15 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/24 13:34:01 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	free(shell->path);
	free(shell->cwd);
	nested_free(shell->buildin_commands);
	nested_free(shell->env);
	free(shell->line);
	free(shell->last_var);
	close(shell->fd_stdin);
	close(shell->fd_stdout);
	free(shell);
}

void			exit_shell(t_shell *shell, int exit_status)
{
	free_tokens(shell);
	free_command(shell);
	free_shell(shell);
	if (exit_status && errno)
		print_error(0, strerror(errno), 1);
	exit(exit_status);
}
