/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:02:11 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/09 17:52:38 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell		*shell;

static int				ft_isspace(char ch)
{
	if ((ch == '\t') || (ch == '\n') || (ch == '\r') ||
			(ch == '\v') || (ch == '\f') || (ch == ' '))
		return (1);
	return (0);
}

void					*free_tokens(t_token *first_token)
{
	t_token				*temp;

	while (first_token)
	{
		temp = first_token;
		first_token = first_token->next;
		free(temp);
	}
	return (0);
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
	if (*line &&
		!(token->next = token_init(ft_strlen(line))))
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
		if (*line == '"')
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
		// else if (*line == '\\')
		// {
		// 	if (!single_quoted)
		// 	{
		// 		line++;
		// 		token->data[i++] = *line++;
		// 	}
		// }
		else if (double_quoted || single_quoted)
		{
			token->data[i++] = *line++;
		}
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
				token = create_next_token(first_token, token, line);
			}
			else if (ft_isspace(*line))
			{
				while (ft_isspace(*line))
					line++;
				if (i)
				{
					token->data[i] = '\0';
					i = 0;
					token = create_next_token(first_token, token, line);
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
				token->data[0] = '>';
				line++;
				if (*line == '>')
				{
					token->data[1] = '>';
					line++;
				}
				token = create_next_token(first_token, token, line);
			}
			else
				token->data[i++] = *line++;
		}
	}
	// if (double_quoted || single_quoted)
	// {
	// 	free_tokens(first_token);
	// 	ft_printf("all quotes must be enclosed\n");
	// 	return (0);
	// }
	return (first_token);
}

static char				*get_var_value(char *var_name)
{
	char				**env_tab;
	char				*var_value;
	int					len;

	var_value = 0;
	env_tab = shell->env;
	len = ft_strlen(var_name);
	while (*env_tab)
	{
		if (!ft_strncmp(*env_tab, var_name, len))
		{
			var_value = ft_strdup((*env_tab) + len);
			break ;
		}
		env_tab++;
	}
	return (var_value);
}

static int				expand_variable(char **new_data, char **data)
{
	char				*var_name;
	char				*var_value;
	char				*temp;
	int					len;
	int					i;

	(*data)++;
	var_name = ft_calloc(ft_strlen(*data), sizeof(char));
	while (**data && **data != '$' && **data != '"' && **data != '\'')
		*var_name++ = *(*data)++;
	var_value = get_var_value(var_name);
	if (!var_value)
		var_value = ft_strdup("");
	free(var_name);
	temp = *new_data;
	len = ft_strlen(*new_data) + ft_strlen(var_value) + ft_strlen(*data) + 1;
	*new_data = ft_calloc(len, sizeof(char));
	ft_strlcat(*new_data, temp, len);
	free(temp);
	i = ft_strlcat(*new_data, var_value, len);
	free(var_value);
	return (i);
}

static void				expand_str(t_token *token)
{
	char				*new_data;
	char				*data;
	int					single_quoted;
	int					double_quoted;
	int					i;

	single_quoted = 0;
	double_quoted = 0;
	i = 0;
	new_data = ft_calloc(ft_strlen(token->data) + 1, sizeof(char));
	data = token->data;
	while (*data)
	{
		if (*data == '\'')
		{
			if (!double_quoted)
			{
				single_quoted = !single_quoted;
				data++;
			}
			else
			{
				new_data[i++] = *data;
				data++;
			}
		}
		else if (*data == '"')
		{
			if (!single_quoted)
			{
				double_quoted = !double_quoted;
				data++;
			}
			else
			{
				new_data[i++] = *data;
				data++;
			}
		}
		else if (*data == '\\')
		{
			data++;
			new_data[i++] = *data;
			if (*data)
				data++;
		}
		else if (*data == '$')
		{
			if (single_quoted)
			{
				new_data[i++] = *data;
				data++;
			}
			else
				i = expand_variable(&new_data, &data);
		}
		else
		{
			new_data[i++] = *data;
			data++;
		}
	}
	free(token->data);
	token->data = new_data;
	if (double_quoted || single_quoted)
	{
		// free_tokens(first_token);
		ft_printf("all quotes must be enclosed\n");
		exit(EXIT_FAILURE);
	}
}

static void				add_arg(t_command *command, char *data)
{
	int					n;
	int					i;
	char				**argv;

	n = 0;
	while (command->argv && command->argv[n])
		n++;
	argv = ft_calloc(n + 2, sizeof(char *));
	i = 0;
	while (i < n)
	{
		argv[i] = command->argv[i];
		i++;
	}
	argv[i] = ft_strdup(data);
	free(command->argv);
	command->argv = argv;
}

t_pipe					*parse_tokens(t_token *token)
{
	t_pipe				*pipe;
	t_token				*first_token;
	t_command			*command;

	pipe = shell->pipe;
	command  = shell->pipe->command;
	first_token = token;
	while (token)
	{
		if (*(token->data) == '<')
		{
			if (!token->next)
			{
				ft_printf("there's no filename after '<'");
				return (free_tokens(first_token));
			}
			token = token->next;
			expand_str(token);
			pipe->input_file_name = ft_strdup(token->data);
			pipe->is_input_from_file = 1;
		}
		else if (*(token->data) == '>')
		{
			if (*(token->data + 1) == '>')
				pipe->is_append = 1;
			if (!token->next)
			{
				ft_printf("there's no filename after '>'");
				return (free_tokens(first_token));
			}
			token = token->next;
			expand_str(token);
			pipe->out_file_name = ft_strdup(token->data);
			pipe->is_out_in_file = 1;
		}
		else if (*(token->data) == '|')
		{
			pipe->is_pipe = 1;
			command->next = ft_calloc(1, sizeof(t_command));
			command = command->next;
		}
		else if (*(token->data) == ';')
		{
			pipe->next = ft_calloc(1, sizeof(t_pipe));
			pipe = pipe->next;
			pipe->command = ft_calloc(1, sizeof(t_command));
			command = pipe->command;
		}
		else
		{
			expand_str(token);
			add_arg(command, token->data);
		}
		token = token->next;
	}
	// free_tokens(first_token);
	return (shell->pipe);
}
