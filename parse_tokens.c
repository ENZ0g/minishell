/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:31:03 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/22 22:48:09 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token			*get_next_token(t_token *token)
{
	if (!token)
		return (0);
	token = token->next;
	return (token);
}

void					free_tokens(t_shell *shell)
{
	t_token		*temp_token;

	while (shell->tokens)
	{
		temp_token = shell->tokens;
		shell->tokens = shell->tokens->next;
		free(temp_token->data);
		free(temp_token);
	}
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
	if (!(argv[i] = ft_strdup(data)))
		exit_shell(shell, EXIT_FAILURE);
	command->argv = argv;
}

static void			ambiguous_redirect_error(t_shell *shell)
{
	g_last_exit_status = 1;
	print_error(shell->last_var, "ambiguous redirect", 1);
	shell->parsing_error = 1;
}

static void			open_file_error(t_shell *shell, char *filename)
{
	print_error(filename, strerror(errno), 1);
	shell->parsing_error = 1;
	g_last_exit_status = 1;
}

static t_token		*redirect_from_file_token(t_shell *shell, t_token *token)
{
	token = get_next_token(token);
	if (expand_str(shell, token, token->data) == -1)
		return (0);
	if (shell->command->file_fd_in)
		close(shell->command->file_fd_in);
	if (!token->data)
		ambiguous_redirect_error(shell);
	else
	{
		if (!(shell->command->input_file_name = ft_strdup(token->data)))
			exit_shell(shell, EXIT_FAILURE);
		shell->command->file_fd_in = open(shell->command->input_file_name,
											O_RDONLY);
		if (shell->command->file_fd_in == -1)
			open_file_error(shell, shell->command->input_file_name);
	}
	free(shell->last_var);
	shell->last_var = 0;
	return (token);
}

static t_token		*redirect_in_file_token(t_shell *shell, t_token *token)
{
	if (*(token->data + 1) == '>')
		shell->command->is_append = 1;
	token = get_next_token(token);
	if (expand_str(shell, token, token->data) == -1)
		return (0);
	if (shell->command->file_fd_out)
		close(shell->command->file_fd_out);
	if (!token->data)
		ambiguous_redirect_error(shell);
	else
	{
		if (!(shell->command->out_file_name = ft_strdup(token->data)))
			exit_shell(shell, EXIT_FAILURE);
		if (shell->command->is_append)
			shell->command->file_fd_out = open(shell->command->out_file_name,
										O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			shell->command->file_fd_out = open(shell->command->out_file_name,
										O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (shell->command->file_fd_out == -1)
			open_file_error(shell, shell->command->out_file_name);
	}
	free(shell->last_var);
	shell->last_var = 0;
	return (token);
}

static t_token		*other_tokens(t_shell *shell, t_token *token)
{
	if (expand_str(shell, token, token->data) == -1)
		return (0);
	if (token->data)
		add_arg(shell, shell->command, token->data);
	free(shell->last_var);
	shell->last_var = 0;
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
			token = get_next_token(token);
			break ;
		}
		else if (shell->parsing_error)
		{
			token = get_next_token(token);
			continue ;
		}
		else if (*(token->data) == '<')
			token = redirect_from_file_token(shell, token);
		else if (*(token->data) == '>')
			token = redirect_in_file_token(shell, token);
		else
			token = other_tokens(shell, token);
		token = get_next_token(token);
	}
	return (token);
}
