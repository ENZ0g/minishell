/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 14:41:14 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/25 16:15:52 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ambiguous_redirect_error(t_shell *shell)
{
	g_last_exit_status = 1;
	print_error(shell->last_var, "ambiguous redirect", 1);
	shell->parsing_error = 1;
}

void		open_file_error(t_shell *shell, char *filename)
{
	if (shell->command->file_fd_in == -1)
		shell->command->file_fd_in = 0;
	if (shell->command->file_fd_out == -1)
		shell->command->file_fd_out = 0;
	print_error(filename, strerror(errno), 1);
	shell->parsing_error = 1;
	g_last_exit_status = 1;
	errno = 0;
}

t_token		*get_next_token(t_token *token)
{
	if (!token)
		return (0);
	token = token->next;
	return (token);
}
