/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:36:20 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/21 15:36:41 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						is_escape_char(char ch)
{
	if (ch == '$' || ch == '"' || ch == '\'' || ch == '\\' ||
		ch == '>' || ch == '<' || ch == '|' || ch == ';')
		return (1);
	return (0);
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
		var_value = ft_itoa(g_last_exit_status);
		(*data)++;
	}
	else
	{
		var_name = ft_calloc(ft_strlen(*data) + 1, sizeof(char));
		i = 0;
		while (**data && ft_isalnum(**data)) // is_alnum(**data)
			var_name[i++] = *(*data)++;
		shell->last_var = ft_strdup(var_name);
		var_value = get_value_by_name(shell, var_name);
		free(var_name);
	}
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

int						expand_str(t_shell *shell, t_token *token)
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
		g_last_exit_status = 258;
		print_error(token->data, "syntax error all quotes must be enclosed", 1);
		shell->parsing_error = 1;
		return (-1);
	}
	return (0);
}