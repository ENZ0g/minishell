/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:48:55 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/25 21:25:40 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*skip_whitespaces(char *str)
{
	while (ft_isspace(*str))
		str++;
	return (str);
}

int			skip_backslashed(t_token *token, char **line, int i)
{
	token->data[i++] = *(*line)++;
	token->data[i++] = *(*line)++;
	return (i);
}

t_token		*token_init(t_shell *shell, size_t len)
{
	t_token		*token;

	if (!(token = ft_calloc(1, sizeof(t_token))) ||
		!(token->data = ft_calloc(len + 1, sizeof(char))))
	{
		free(token);
		exit_shell(shell, EXIT_FAILURE);
	}
	return (token);
}

t_token		*create_next_token(t_shell *shell, t_token *token, char *line)
{
	token->next = token_init(shell, ft_strlen(line));
	return (token->next);
}

void		remove_last_token(t_shell *shell)
{
	t_token		*token;

	token = shell->tokens;
	while (token && token->next && token->next->next)
		token = token->next;
	if (token && token->next)
	{
		free(token->next->data);
		free(token->next);
		token->next = 0;
	}
	else if (token)
		free_tokens(shell);
}
