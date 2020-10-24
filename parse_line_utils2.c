/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:56:35 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/24 13:57:59 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		process_single_quote(t_quotes *quote, t_token *token,
									char **line, int i)
{
	if (!quote->d_quote)
		quote->s_quote = !quote->s_quote;
	token->data[i++] = *(*line)++;
	return (i);
}

int		process_double_quote(t_quotes *quote, t_token *token,
									char **line, int i)
{
	if (!quote->s_quote)
		quote->d_quote = !quote->d_quote;
	token->data[i++] = *(*line)++;
	return (i);
}

int		process_operators(t_shell *shell, t_token **token,
										char **line, int i)
{
	if (i)
	{
		(*token)->data[i] = '\0';
		i = 0;
		(*token)->next = token_init(shell, 1);
		*token = (*token)->next;
	}
	(*token)->data[0] = *(*line)++;
	if (**line)
		*token = create_next_token(shell, *token, *line);
	return (i);
}

int		process_whitespaces(t_shell *shell, t_token **token,
										char **line, int i)
{
	while (ft_isspace(**line))
		(*line)++;
	if (i)
	{
		(*token)->data[i] = '\0';
		i = 0;
		if (**line)
			*token = create_next_token(shell, *token, *line);
	}
	return (i);
}

int		process_out_operator(t_shell *shell, t_token **token,
										char **line, int i)
{
	if (i)
	{
		(*token)->data[i] = '\0';
		i = 0;
		if (*(*line + 1) == '>')
			(*token)->next = token_init(shell, 2);
		else
			(*token)->next = token_init(shell, 1);
		*token = (*token)->next;
	}
	(*token)->data[0] = *(*line)++;
	if (**line == '>')
		(*token)->data[1] = *(*line)++;
	if (**line)
		*token = create_next_token(shell, *token, *line);
	return (i);
}
