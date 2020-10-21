/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:02:11 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/20 21:55:50 by jnannie          ###   ########.fr       */
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


static t_token			*token_init(size_t len)
{
	t_token				*token;

	token = 0;
	if (!(token = ft_calloc(1, sizeof(t_token))) ||
		!(token->data = ft_calloc(len + 1, sizeof(char))))
	{
		free(token);
		return (0);
	}
	return (token);
}

static t_token			*create_next_token(t_token *first_token, t_token *token, char *line)
{
	if (!(token->next = token_init(ft_strlen(line))))
		return (free_tokens(first_token));
	return (token->next);
}



t_token					*parse_line(char *line)
{
	int					double_quoted;
	int					single_quoted;
	int					i;
	t_token				*token;
	t_token				*first_token; //save it maybe in some global structure

	double_quoted = 0;
	single_quoted = 0;
	i = 0;
	if (!(first_token = token_init(ft_strlen(line))))
		return (0);
	token = first_token;
	while (*line)
	{
		if (*line == '\\')
		{
			if (((is_escape_char(*(line + 1)) || *(line + 1) == ' ') && !single_quoted) ||
				(!single_quoted && !double_quoted))
			{
				token->data[i++] = *line++;		//!!
				token->data[i++] = *line++;		//!!
			}
			else
			{
				token->data[i++] = *line++;		//!!
				token->data[i++] = *line++;		//!!
			}
		}
		else if (*line == '"')
		{
			if (!single_quoted)
				double_quoted = !double_quoted;
			token->data[i++] = *line++;
		}
		else if (*line == '\'')
		{
			if (!double_quoted)
				single_quoted = !single_quoted;
			token->data[i++] = *line++;
		}
		else if (double_quoted || single_quoted)
			token->data[i++] = *line++;
		else if (!double_quoted && !single_quoted)
		{
			if (ft_strchr(";|<", *line))
			{
				if (i)
				{
					token->data[i] = '\0';
					i = 0;
					if (!(token->next = token_init(1)))
						return (free_tokens(first_token));
					token = token->next;
				}
				token->data[0] = *line++;
				if (*line &&
					!(token = create_next_token(first_token, token, line)))
						return (free_tokens(first_token));
			}
			else if (ft_isspace(*line))
			{
				while (ft_isspace(*line))
					line++;
				if (i)
				{
					token->data[i] = '\0';
					i = 0;
					if (*line &&
						!(token = create_next_token(first_token, token, line)))
							return (free_tokens(first_token));
				}
			}
			else if (*line == '>')
			{
				if (i)
				{
					token->data[i] = '\0';
					i = 0;
					if (*(line + 1) == '>')
					{
						if (!(token->next = token_init(2)))
							return (free_tokens(first_token));
					}
					else if (!(token->next = token_init(1)))
						return (free_tokens(first_token));
					token = token->next;
				}
				token->data[0] = *line++;
				if (*line == '>')
					token->data[1] = *line++;
				if (*line &&
					!(token = create_next_token(first_token, token, line)))
						return (free_tokens(first_token));
			}
			else
				token->data[i++] = *line++;
		}
	}
	return (first_token);
}















