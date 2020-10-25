/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 00:10:15 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/24 20:43:11 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			free_command(t_shell *shell)
{
	if (!shell || !shell->command)
		return ;
	free(shell->command->correct_path);
	nested_free(shell->command->argv);
	free(shell->command->out_file_name);
	free(shell->command->input_file_name);
	if (shell->command->file_fd_in)
		close(shell->command->file_fd_in);
	if (shell->command->file_fd_out)
		close(shell->command->file_fd_out);
	free(shell->command);
	shell->command = 0;
}

void			free_tokens(t_shell *shell)
{
	t_token		*temp_token;

	while (shell && shell->tokens)
	{
		temp_token = shell->tokens;
		shell->tokens = shell->tokens->next;
		free(temp_token->data);
		free(temp_token);
	}
	shell->tokens = 0;
}

static void		free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	nested_free(shell->path);
	free(shell->cwd);
	nested_free(shell->buildin_commands);
	nested_free(shell->env);
	free(shell->line);
	free(shell->last_var);
	close(shell->fd_stdin);
	close(shell->fd_stdout);
	free(shell->buf);
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
