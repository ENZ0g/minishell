/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 15:02:11 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/20 15:54:13 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *error_source, char *error_msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (error_source)
	{
		ft_putstr_fd(error_source, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error_msg, 2);
	// ft_putstr_fd("\n", 2);
}

static int				ft_isspace(char ch)
{
	if ((ch == '\t') || (ch == '\n') || (ch == '\r') ||
			(ch == '\v') || (ch == '\f') || (ch == ' '))
		return (1);
	return (0);
}

static t_token			*free_and_get_next_token(t_token *token)
{
	t_token		*temp_token;

	temp_token = token;
	token = token->next;
	free(temp_token->data);
	free(temp_token);
	return (token);
}

void					*free_tokens(t_token *token)
{
	while (token)
		token = free_and_get_next_token(token);
	return (0);
}

// void					free_pipes(t_shell *shell)
// {
// 	t_pipe		*pipe;
// 	t_pipe		*temp_pipe;
// 	t_command	*temp_command;
// 	char		**temp_argv;
// 	t_command	*command;

// 	pipe = shell->pipe;
// 	while (pipe)
// 	{
// 		command = pipe->command;
// 		while (command)
// 		{
// 			temp_argv = command->argv;
// 			while (temp_argv && *temp_argv)
// 			{
// 				free(*temp_argv);
// 				temp_argv++;
// 			}
// 			free(command->argv);
// 			temp_command = command;
// 			command = command->next;
// 			free(temp_command);
// 		}
// 		temp_pipe = pipe;
// 		pipe = pipe->next;
// 		free(temp_pipe);
// 	}
// }

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

static int				is_escape_char(char ch)
{
	if (ch == '$' || ch == '"' || ch == '\'' ||
		ch == '>' || ch == '<' || ch == '|' || ch == ';')
		return (1);
	return (0);
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
				token->data[i++] = *line++;
				token->data[i++] = *line++;
			}
			else
			{
				token->data[i++] = *line++;
				token->data[i++] = *line++;
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

static char				*get_value_by_name(t_shell *shell, char *var_name) // PATH=sdfbsdfg/sdfgsdfg/
{
	char				**env_tab;
	char				*var_value;
	int					len;

	var_value = 0;
	env_tab = shell->env;
	len = ft_strlen(var_name);
	while (*env_tab)
	{
		if (!ft_strncmp(*env_tab, var_name, len) && *((*env_tab) + len) == '=')
		{
			var_value = ft_strdup((*env_tab) + len + 1);
			break ;
		}
		env_tab++;
	}
	return (var_value);
}

static int				expand_variable(t_shell *shell, char **new_data, char **data)
{
	char				*var_name;
	char				*var_value;
	char				*temp;
	int					len;
	int					i;

	(*data)++;
	if (!ft_isalpha(**data) && **data != '?')
		return(ft_strlcat(*new_data, "$", ft_strlen(*new_data) + 2));
	if (**data == '?')
	{
		var_name = 0;
		var_value = ft_itoa(shell->last_exit_status);
		(*data)++;
	}
	else
	{
		var_name = ft_calloc(ft_strlen(*data) + 1, sizeof(char));
		i = 0;
		while (**data && ft_isalnum(**data)) // is_alnum(**data)
			var_name[i++] = *(*data)++;
		var_value = get_value_by_name(shell, var_name);
		free(var_name);
	}
	// ft_printf("%s\n", var_name); exit(EXIT_FAILURE);
	if (!var_value)
		var_value = ft_strdup("");
	temp = *new_data;
	len = ft_strlen(*new_data) + ft_strlen(var_value) + ft_strlen(*data) + 1;
	*new_data = ft_calloc(len, sizeof(char));
	ft_strlcat(*new_data, temp, len);
	free(temp);
	i = ft_strlcat(*new_data, var_value, len);
	free(var_value);
	return (i);
}

static int				expand_str(t_shell *shell, t_token *token)
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
			if ((is_escape_char(*(data + 1)) && !single_quoted) ||
				(!single_quoted && !double_quoted))
			{
				data++;
				new_data[i++] = *data++;
			}
			else
				new_data[i++] = *data++;
		}
		// else if (*data == '\\')
		// {
		// 	data++;
		// 	new_data[i++] = *data;
		// 	if (*data)
		// 		data++;
		// }
		else if (*data == '$')
		{
			if (single_quoted)
			{
				new_data[i++] = *data;
				data++;
			}
			else if ((i = expand_variable(shell, &new_data, &data)) == 0 && *data == '\0')
			{
				free(token->data);
				token->data = 0;
				free(new_data);
				return (0);
			}
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
		print_error(data, "syntax error all quotes must be enclosed\n");
		shell->parsing_error = 1;
		return (-1);
	}
	return (0);
}

int		is_buildin_command(t_shell *shell, char *command)
{
	int	i;

	i = 0;
	while (shell->buildin_commands[i])
	{
		if (ft_strcmp(command, shell->buildin_commands[i]))
			return (1);
		i++;
	}
	return (0);
}

void	check_correct_command(t_shell *shell, t_command *command, char *data)
{
	int			i;
	struct stat	status_struct;
	char		*total_path;

	if (is_buildin_command(shell, data))
		return ;
	if (data[0] == '.')
	{
		total_path = ft_strjoin(shell->cwd, data + 1);
		if (stat(total_path, &status_struct) == 0 && (status_struct.st_mode & S_IFMT) == S_IFREG)
		{
			command->correct_path = ft_strdup(total_path);
			// command->is_found = 1;
			free(total_path);
			return ;
		}
	}
	if (data[0] == '/')
	{
		if (stat(data, &status_struct) == 0 && (status_struct.st_mode & S_IFMT) == S_IFREG)
		{
			command->correct_path = ft_strdup(data);
			// command->is_found = 1;
			return ;
		}
	}
	command->is_found = 0;
	i = 0;
	while (shell->path[i])
	{
		total_path = ft_strjoin(shell->path[i], data);
		if (stat(total_path, &status_struct) == 0 && (status_struct.st_mode & S_IFMT) == S_IFREG)
		{
			command->correct_path = ft_strdup(total_path);
			command->is_found = 1;
		}
		free(total_path);
		i++;
	}
	if (command->is_found == 0)
		print_error(data, "command not found\n");

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

static int				check_for_forbidden_token(t_shell *shell, t_token *token, char *forbidden_tokens)
{
	if (!token)
	{
		print_error(0, "syntax error near unexpected token `newline'\n");
		shell->parsing_error = 1;
		return (-1);
	}
	else if (token->data == 0)
	{
		if (*forbidden_tokens == '<')
			print_error(0, "ambiguous redirect"); //echo hello > $HKLDSF
		shell->parsing_error = 1;
		return (-1);
	}
	else if (ft_strchr(forbidden_tokens, *(token->data)))
	{
		print_error(0, "syntax error near unexpected token `");
		ft_putstr_fd(token->data, 2);
		ft_putstr_fd("'\n", 2);
		// ft_printf("syntax error near unexpected token %s\n", token->data);
		shell->parsing_error = 1;
		return (-1);
	}
	return (0);
}

t_token				*parse_tokens(t_shell *shell, t_token *token)
{
	int		is_first_token;
	// t_token				*temp_token;
	// t_command			*command;

	// shell->command = ft_calloc(1, sizeof(t_command));
	// command  = shell->command;
	// free(shell->command);
	shell->command = ft_calloc(1, sizeof(t_command));
	is_first_token = 1;
	// first_token = token;
	while (token)
	{
		if (*(token->data) == '<')
		{
			if (check_for_forbidden_token(shell, token->next, "<>;|") == -1)
				return (free_tokens(token));
			token = free_and_get_next_token(token);
			if (expand_str(shell, token) == -1)
				return (free_tokens(token));
			shell->command->input_file_name = ft_strdup(token->data);
			shell->command->is_input_from_file = 1;
		}
		else if (*(token->data) == '>')
		{
			if (*(token->data + 1) == '>')
			{
				shell->command->is_append = 1;
				if (check_for_forbidden_token(shell, token->next, "<>;|") == -1)
					return (free_tokens(token));			}
			if (check_for_forbidden_token(shell, token->next, "<;|") == -1)
				return (free_tokens(token));
			token = free_and_get_next_token(token);
			if (expand_str(shell, token) == -1)
				return (free_tokens(token));
			shell->command->out_file_name = ft_strdup(token->data);
			shell->command->is_out_in_file = 1;
		}
		else if (*(token->data) == '|')		// if is in first place should return error "unexpected token"
		{
			if (is_first_token)
			{
				check_for_forbidden_token(shell, token, "|");
				return (free_tokens(token));
			}
			else if (check_for_forbidden_token(shell, token->next, ";|") == -1)
				return (free_tokens(token));
			shell->command->is_pipe = 1;
			token = free_and_get_next_token(token);
			break ;
			// command->next = ft_calloc(1, sizeof(t_command));
			// command = command->next;
		}
		else if (*(token->data) == ';')		// if is in first place should return error "unexpected token"
		{
			if (is_first_token)
			{
				check_for_forbidden_token(shell, token, ";");
				return (free_tokens(token));
			}
			else if (check_for_forbidden_token(shell, token->next, ";|") == -1)
				return (free_tokens(token));
			token = free_and_get_next_token(token);
			break ;
			// command->next = ft_calloc(1, sizeof(t_command));
			// command = command->next;
		}
		else
		{
			if (expand_str(shell, token) == -1)
				return (free_tokens(token));
			if (token->data)
				add_arg(shell, shell->command, token->data);
		}
		is_first_token = 0;
		token = free_and_get_next_token(token);
	}
	return (token);
}

int		check_tokens(t_shell *shell, t_token *tokens)
{
	int		is_first_token;

	is_first_token = 1;
	while (tokens)
	{
		if (*(tokens->data) == '<')
		{
			if (check_for_forbidden_token(shell, tokens->next, "<>;|") == -1)
				return (-1);
		}
		else if (*(tokens->data) == '>')
		{
			if (*(tokens->data + 1) == '>')
			{
				if (check_for_forbidden_token(shell, tokens->next, "<>;|") == -1)
					return (-1);			}
			if (check_for_forbidden_token(shell, tokens->next, "<;|") == -1)
				return (-1);
		}
		else if (*(tokens->data) == '|')
		{
			if (is_first_token)
			{
				check_for_forbidden_token(shell, tokens, "|");
				return (-1);
			}
			else if (check_for_forbidden_token(shell, tokens->next, ";|") == -1)
				return (-1);
		}
		else if (*(tokens->data) == ';')
		{
			if (is_first_token)
			{
				check_for_forbidden_token(shell, tokens, ";");
				return (-1);
			}
			else if (check_for_forbidden_token(shell, tokens->next, ";|") == -1)
				return (-1);
		}
		is_first_token = 0;
		tokens = tokens->next;
	}
	return (0);
}
