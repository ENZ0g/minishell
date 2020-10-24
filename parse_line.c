/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:02:11 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/24 13:58:39 by rhullen          ###   ########.fr       */
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

	quote.s_quote = 0;
	quote.d_quote = 0;
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
		else if (quote.d_quote || quote.s_quote)
			token->data[i++] = *line++;
		else if (!quote.d_quote && !quote.s_quote)
			i = process_not_quoted(shell, &token, &line, i);
	return (first_token);
}
