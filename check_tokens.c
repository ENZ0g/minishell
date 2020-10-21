/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:44:37 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/21 15:33:35 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				check_for_forbidden_token(t_shell *shell, t_token *token, char *forbidden_tokens, int is_newline_forbidden)
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

int					check_tokens(t_shell *shell, t_token *token)
{
	int			is_first_token;
	// t_token		*first_token;

	is_first_token = 1;
	// first_token = tokens;
	while (token)
	{
		if (*(token->data) == '|')
		{
			if (is_first_token)
			{
				check_for_forbidden_token(shell, token, "|", 1);
				return (0);
			}
			else if (check_for_forbidden_token(shell, token->next, ";|", 1) == -1)
				return (0);
		}
		else if (*(token->data) == ';')
		{
			if (is_first_token)
			{
				check_for_forbidden_token(shell, token, ";", 0);
				return (0);
			}
			else if (check_for_forbidden_token(shell, token->next, ";|", 0) == -1)
				return (0);
		}
		else if (*(token->data) == '<')
		{
			if (check_for_forbidden_token(shell, token->next, "<>;|", 1) == -1)
				return (0);
		}
		else if (*(token->data) == '>')
		{
			if (*(token->data + 1) == '>')
			{
				if (check_for_forbidden_token(shell, token->next, "<>;|", 1) == -1)
					return (0);
			}
			if (check_for_forbidden_token(shell, token->next, "<;|", 1) == -1)
				return (0);
		}
		is_first_token = 0;
		token = token->next;
	}
	return (1);
}