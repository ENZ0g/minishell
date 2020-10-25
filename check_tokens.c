/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:44:37 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/25 21:12:18 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_forbidden_token(t_shell *shell, t_token *token,
						char *forbidden_tokens, int is_newline_forbidden)
{
	if (!token)
	{
		if (!is_newline_forbidden)
			return (0);
		g_last_exit_status = 258;
		print_error(0, "syntax error near unexpected token `newline'", 1);
		shell->parsing_error = 1;
		return (-1);
	}
	else if (ft_strchr(forbidden_tokens, *(token->data)))
	{
		g_last_exit_status = 258;
		print_error(0, "syntax error near unexpected token `", 0);
		ft_putstr_fd(token->data, 2);
		ft_putstr_fd("'\n", 2);
		shell->parsing_error = 1;
		return (-1);
	}
	return (0);
}

int		check_pipe_token(t_shell *shell, t_token *token,
							int is_first)
{
	if (is_first)
	{
		check_forbidden_token(shell, token, "|", 1);
		return (-1);
	}
	else if (check_forbidden_token(shell, token->next, ";|", 1) == -1)
		return (-1);
	return (0);
}

int		check_end_token(t_shell *shell, t_token *token,
							int is_first)
{
	if (is_first)
	{
		check_forbidden_token(shell, token, ";", 0);
		return (-1);
	}
	else if (check_forbidden_token(shell, token->next, ";|", 0) == -1)
		return (-1);
	return (0);
}

int		check_redirect_out_token(t_shell *shell, t_token *token)
{
	if (*(token->data + 1) == '>')
	{
		if (check_forbidden_token(shell, token->next, "<>;|", 1) == -1)
			return (-1);
	}
	if (check_forbidden_token(shell, token->next, "<;|", 1) == -1)
		return (-1);
	return (0);
}

int		check_tokens(t_shell *shell, t_token *token)
{
	int	is_first;
	int	check;

	is_first = 1;
	check = 0;
	while (token)
	{
		if (*(token->data) == '|')
			check = check_pipe_token(shell, token, is_first);
		else if (*(token->data) == ';')
			check = check_end_token(shell, token, is_first);
		else if (*(token->data) == '<')
			check = check_forbidden_token(shell, token->next, "<>;|", 1);
		else if (*(token->data) == '>')
			check = check_redirect_out_token(shell, token);
		if (check == -1)
			return (0);
		is_first = 0;
		token = token->next;
	}
	return (1);
}
