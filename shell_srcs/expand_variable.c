/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 19:51:01 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/24 14:00:36 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				cat_data(t_shell *shell, char **new_data,
									char *var_value, char **data)
{
	char				*temp;
	int					len;
	int					i;

	temp = *new_data;
	len = ft_strlen(*new_data) + ft_strlen(var_value) + ft_strlen(*data) + 1;
	if (!(*new_data = ft_calloc(len, sizeof(char))))
	{
		free(var_value);
		free(*new_data);
		exit_shell(shell, EXIT_FAILURE);
	}
	ft_strlcat(*new_data, temp, len);
	free(temp);
	i = ft_strlcat(*new_data, var_value, len);
	free(var_value);
	return (i);
}

static char				*get_value_by_name_and_free_varname(t_shell *shell,
															char *var_name)
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
			if (!(var_value = ft_strdup((*env_tab) + len + 1)))
			{
				free(var_name);
				return (0);
			}
		}
		env_tab++;
	}
	free(var_name);
	if (!var_value)
		var_value = ft_strdup("");
	return (var_value);
}

static void				free_data_and_exit(t_shell *shell, char **new_data,
											char *var_name)
{
	free(var_name);
	free(*new_data);
	exit_shell(shell, EXIT_FAILURE);
}

static void				set_last_var(t_shell *shell, char **new_data,
									char *var_name)
{
	char		*temp;
	char		*temp_var;

	temp_var = 0;
	if (!(temp = ft_strjoin("$", var_name)))
		free_data_and_exit(shell, new_data, var_name);
	if (!shell->last_var)
	{
		if (!(shell->last_var = ft_strdup(temp)))
			free_data_and_exit(shell, new_data, var_name);
	}
	else
	{
		temp_var = shell->last_var;
		if (!(shell->last_var = ft_strjoin(shell->last_var, temp)))
			free_data_and_exit(shell, new_data, var_name);
	}
	free(temp);
	free(temp_var);
}

int						expand_variable(t_shell *shell, char **new_data,
										char **data)
{
	char				*var_name;
	char				*var_value;
	int					i;

	(*data)++;
	if (!ft_isalpha(**data) && **data != '?' && **data != '_')
		return (ft_strlcat(*new_data, "$", ft_strlen(*new_data) + 2));
	if (**data == '?')
	{
		if (!(var_value = ft_itoa(g_last_exit_status)))
			free_data_and_exit(shell, new_data, 0);
		(*data)++;
	}
	else
	{
		if (!(var_name = ft_calloc(ft_strlen(*data) + 1, sizeof(char))))
			free_data_and_exit(shell, new_data, 0);
		i = 0;
		while (**data && ft_isalnum(**data))
			var_name[i++] = *(*data)++;
		set_last_var(shell, new_data, var_name);
		if (!(var_value = get_value_by_name_and_free_varname(shell, var_name)))
			free_data_and_exit(shell, new_data, 0);
	}
	return (cat_data(shell, new_data, var_value, data));
}
