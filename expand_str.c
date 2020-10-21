/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:36:20 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/22 01:56:36 by jnannie          ###   ########.fr       */
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

static void				set_last_var(t_shell *shell, char *var_name)
{
	char		*temp;
	char		*temp_var;

	temp_var = 0;
	temp = ft_strjoin("$", var_name);
	if (!shell->last_var)
		shell->last_var = ft_strdup(temp);
	else
	{
		temp_var = shell->last_var;
		shell->last_var = ft_strjoin(shell->last_var, temp);
	}
	free(temp);
	free(temp_var);
}

static int				cat_data(t_shell *shell, char **new_data,
									char *var_value, char **data)
{
	char				*temp;
	int					len;
	int					i;

	if (!var_value)
		if (!(var_value = ft_strdup("")))
			exit_shell(shell, EXIT_FAILURE);
	temp = *new_data;
	len = ft_strlen(*new_data) + ft_strlen(var_value) + ft_strlen(*data) + 1;
	if (!(*new_data = ft_calloc(len, sizeof(char))))
		exit_shell(shell, EXIT_FAILURE);
	ft_strlcat(*new_data, temp, len);
	free(temp);
	i = ft_strlcat(*new_data, var_value, len);
	free(var_value);
	return (i);
}

static int				expand_variable(t_shell *shell, char **new_data, char **data)
{
	char				*var_name;
	char				*var_value;
	int					i;

	(*data)++;
	if (!ft_isalpha(**data) && **data != '?' && **data != '_')
		return (ft_strlcat(*new_data, "$", ft_strlen(*new_data) + 2));
	if (**data == '?')
	{
		var_name = 0;
		var_value = ft_itoa(g_last_exit_status);
		(*data)++;
	}
	else
	{
		if (!(var_name = ft_calloc(ft_strlen(*data) + 1, sizeof(char))))
			exit_shell(shell, EXIT_FAILURE);
		i = 0;
		while (**data && ft_isalnum(**data))
			var_name[i++] = *(*data)++;
		set_last_var(shell, var_name);
		var_value = get_value_by_name(shell, var_name);
		free(var_name);
	}
	return (cat_data(shell, new_data, var_value, data));
}

static int				check_quotes_error(int single_q, int double_q,
											t_shell *shell, t_token *token)
{
	if (double_q || single_q)
	{
		g_last_exit_status = 258;
		print_error(token->data, "syntax error all quotes must be enclosed", 1);
		shell->parsing_error = 1;
		return (-1);
	}
	return (0);
}

static int				process_quote(int quote1, int quote2,
									char **temp_data, char **data)
{
	if (!quote1)
		quote2 = !quote2;
	else
		*(*temp_data)++ = **data;
	(*data)++;
	return (quote2);
}

static char				*proc_var(t_shell *shell, char **new_data,
										char **data, t_token *token)
{
	int		i;

	if ((i = expand_variable(shell, new_data, data)) == 0 && **data == '\0')
	{
		free(token->data);
		token->data = 0;
		free(*new_data);
		return (0);
	}
	else
		return (*new_data + i);
}

static void				process_backslash(int single_q, int double_q,
										char **temp_data, char **data)
{
	if ((is_escape_char(*(*data + 1)) && !single_q) ||
		(!single_q && !double_q))
		(*data)++;
	*(*temp_data)++ = *(*data)++;
}

static char				*init_vars(t_shell *shell, int *single_q, int *double_q,
								char **new_data, char *data)
{
	*single_q = 0;
	*double_q = 0;
	if (!(*new_data = ft_calloc(ft_strlen(data) + 1, sizeof(char))))
		exit_shell(shell, EXIT_FAILURE);
	return (*new_data);
}

int						expand_str(t_shell *shell, t_token *token, char *data)
{
	char				*new_data;
	int					single_q;
	int					double_q;
	char				*temp_data;

	temp_data = init_vars(shell, &single_q, &double_q, &new_data, data);
	while (*data)
		if (*data == '\'')
			single_q = process_quote(double_q, single_q, &temp_data, &data);
		else if (*data == '"')
			double_q = process_quote(single_q, double_q, &temp_data, &data);
		else if (*data == '\\')
			process_backslash(single_q, double_q, &temp_data, &data);
		else if (*data == '$')
		{
			if (single_q)
				*temp_data++ = *data++;
			else if (!(temp_data = proc_var(shell, &new_data, &data, token)))
				return (0);
		}
		else
			*temp_data++ = *data++;
	free(token->data);
	token->data = new_data;
	return (check_quotes_error(single_q, double_q, shell, token));
}