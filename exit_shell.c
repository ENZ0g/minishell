/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:10:15 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/21 15:51:51 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	total_free(t_shell *shell)
{
	free(shell->path);
	free(shell->cwd);
	free(shell->last_command);
	nested_free(shell->buildin_commands);
	nested_free(shell->env);
}

void		exit_shell(t_shell *shell, int exit_status)
{
	free_tokens(shell->tokens);
	free_command(shell);
	total_free(shell);
	exit(exit_status);
}
