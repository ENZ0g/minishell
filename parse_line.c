/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:02:11 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/24 15:01:38 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				process_not_quoted(t_shell *shell, t_token **token,
										char **line, int i)
{
	if (ft_strchr(";|<", **line))
		i = process_operators(shell, token, line, i);
	else if (ft_isspace(**line))
		i = process_whitespaces(shell, token, line, i);
	else if (**line == '>')
		i = process_out_operator(shell, token, line, i);
	else
		(*token)->data[i++] = *(*line)++;
	return (i);
}

t_token					*parse_line(t_shell *shell, char *line)
{
	t_quotes			quote;
	int					i;
	t_token				*token;
	t_token				*first_token;

	quote.sq = 0;
	quote.dq = 0;
	i = 0;
	first_token = token_init(shell, ft_strlen(line));
	shell->tokens = first_token;
	token = first_token;
	while (*line)
		if (*line == '\\')
			i = skip_backslashed(token, &line, i);
		else if (*line == '"')
			i = process_double_quote(&quote, token, &line, i);
		else if (*line == '\'')
			i = process_single_quote(&quote, token, &line, i);
		else if (quote.dq || quote.sq)
			token->data[i++] = *line++;
		else if (!quote.dq && !quote.sq)
			i = process_not_quoted(shell, &token, &line, i);
	return (first_token);
}
