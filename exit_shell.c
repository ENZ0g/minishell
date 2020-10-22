/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:10:15 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/23 00:00:31 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_shell(t_shell *shell)
{
	free(shell->path);
	free(shell->cwd);
	// free(shell->last_command);
	nested_free(shell->buildin_commands);
	nested_free(shell->env);
	free(shell->line);
	free(shell->last_var);
}

void			exit_shell(t_shell *shell, int exit_status)
{
	free_tokens(shell);
	free_command(shell);
	free_shell(shell);
	exit(exit_status);
}
