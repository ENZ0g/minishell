/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:31:03 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/21 17:16:02 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token			*free_and_get_next_token(t_token *token)
{
	t_token		*temp_token;

	if (!token)
		return (0);
	temp_token = token;
	token = token->next;
	free(temp_token->data);
	free(temp_token);
	return (token);
}

void					*free_tokens(t_token *token)
{
	while (token)
		token = free_and_get_next_token(token);
	return (0);
}


static void				add_arg(t_shell *shell, t_command *command, char *data)
{
	int					n;
	int					i;
	char				**argv;

	if (data == 0)
		return ;
	if (command->argv == 0)
		check_correct_command(shell, command, data);
	n = 0;
	while (command->argv && command->argv[n])
		n++;
	if (!(argv = ft_calloc(n + 2, sizeof(char *))))
		exit_shell(shell, EXIT_FAILURE);
	i = 0;
	while (i < n)
	{
		argv[i] = command->argv[i];
		i++;
	}
	argv[i] = ft_strdup(data);
	command->argv = argv;
}

static void			ambiguous_redirect_error(t_shell *shell)
{
	g_last_exit_status = 1;
	print_error(0, "$", 0);
	ft_putstr_fd(shell->last_var, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	shell->parsing_error = 1;
	free(shell->last_var);
}

static void			open_file_error(t_shell *shell)
{
	print_error(shell->command->out_file_name, strerror(errno), 1);
	shell->parsing_error = 1;
	g_last_exit_status = 1;
}

static t_token		*redirect_from_file_token(t_shell *shell, t_token *token)
{
	token = free_and_get_next_token(token);
	if (expand_str(shell, token) == -1)
		return (free_tokens(token));
	if (shell->command->file_fd_in)
		close(shell->command->file_fd_in);
	if (!token->data)
		ambiguous_redirect_error(shell);
	else
	{
		shell->command->input_file_name = ft_strdup(token->data);
		shell->command->file_fd_in = open(shell->command->input_file_name,
											O_RDONLY);
		if (shell->command->file_fd_in == -1)
			open_file_error(shell);
	}
	return (token);
}

static t_token		*redirect_in_file_token(t_shell *shell, t_token *token)
{
	if (*(token->data + 1) == '>')
		shell->command->is_append = 1;
	token = free_and_get_next_token(token);
	if (expand_str(shell, token) == -1)
		return (free_tokens(token));
	if (shell->command->file_fd_out)
		close(shell->command->file_fd_out);
	if (!token->data)
		ambiguous_redirect_error(shell);
	else
	{
		shell->command->out_file_name = ft_strdup(token->data);
		if (shell->command->is_append)
			shell->command->file_fd_out = open(shell->command->out_file_name,
										O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			shell->command->file_fd_out = open(shell->command->out_file_name,
										O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (shell->command->file_fd_out == -1)
			open_file_error(shell);
	}
	return (token);
}

static t_token		*other_tokens(t_shell *shell, t_token *token)
{
	if (expand_str(shell, token) == -1)
		return (free_tokens(token));
	if (token->data)
		add_arg(shell, shell->command, token->data);
	return (token);
}

t_token				*parse_tokens(t_shell *shell, t_token *token)
{
	if (!(shell->command = ft_calloc(1, sizeof(t_command))))
		exit_shell(shell, EXIT_FAILURE);
	while (token)
	{
		if (*(token->data) == '|' || *(token->data) == ';')
		{
			if (*(token->data) == '|')
				shell->command->is_pipe = 1;
			token = free_and_get_next_token(token);
			break ;
		}
		else if (shell->parsing_error)
		{
			token = free_and_get_next_token(token);
			continue ;
		}
		else if (*(token->data) == '<')
			token = redirect_from_file_token(shell, token);
		else if (*(token->data) == '>')
			token = redirect_in_file_token(shell, token);
		else
			token = other_tokens(shell, token);
		token = free_and_get_next_token(token);
	}
	return (token);
}
