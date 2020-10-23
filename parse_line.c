/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:02:11 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/23 16:13:44 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					print_error(char *error_source, char *error_msg, int new_line)
{
	ft_putstr_fd("minishell: ", 2);
	if (error_source)
	{
		ft_putstr_fd(error_source, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error_msg, 2);
	if (new_line)
		ft_putstr_fd("\n", 2);
}

static int				ft_isspace(char ch)
{
	if ((ch == '\t') || (ch == '\n') || (ch == '\r') ||
			(ch == '\v') || (ch == '\f') || (ch == ' '))
		return (1);
	return (0);
}

char					*skip_whitespaces(char *str)
{
	while (ft_isspace(*str))
		str++;
	return (str);
}


static t_token			*token_init(t_shell *shell, size_t len)
{
	t_token				*token;

	if (!(token = ft_calloc(1, sizeof(t_token))) ||
		!(token->data = ft_calloc(len + 1, sizeof(char))))
	{
		free(token);
		exit_shell(shell, EXIT_FAILURE);
	}
	return (token);
}

static t_token			*create_next_token(t_shell *shell, t_token *token, char *line)
{
	token->next = token_init(shell, ft_strlen(line));
	return (token->next);
}

static int				process_single_quote(t_quotes *quote, t_token *token,
									char **line, int i)
{
	if (!quote->d_quote)
		quote->s_quote = !quote->s_quote;
	token->data[i++] = *(*line)++;
	return (i);
}

static int				process_double_quote(t_quotes *quote, t_token *token,
									char **line, int i)
{
	if (!quote->s_quote)
		quote->d_quote = !quote->d_quote;
	token->data[i++] = *(*line)++;
	return (i);
}

static int				process_operators(t_shell *shell, t_token **token,
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

static int				process_whitespaces(t_shell *shell, t_token **token,
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

static int				process_out_operator(t_shell *shell, t_token **token,
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

static int				skip_backslashed(t_token *token, char **line, int i)
{
	token->data[i++] = *(*line)++;
	token->data[i++] = *(*line)++;
	return (i);
}

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















