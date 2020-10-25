/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:18:46 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/25 16:40:18 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_export_name_valid(char *name)
{
	if (!ft_isalpha(*name++))
		return (0);
	while (*name)
	{
		if (*name != '_' && !ft_isalnum(*name) && *name != '=')
			return (0);
		name++;
	}
	return (1);
}

/*
** export
** Sets new env variable.
** Upds variable's value if variable is in env list.
** Adds variable with its value if variable is not in env list.
*/

void	export(t_shell *shell, t_command *command)
{
	int		i;
	char	*variable;
	char	*value;

	i = 1;
	while (command->argv[i])
	{
		if (!is_export_name_valid(command->argv[i]))
		{
			ft_printf_error("minishell: export: `%s': not a valid "\
							"identifier\n", command->argv[i]);
			g_last_exit_status = 1;
			i++;
			continue ;
		}
		variable = get_var_name(shell, command->argv[i]);
		value = get_var_value(shell, command->argv[i]);
		if (check_env_exist(shell, variable))
			upd_env(shell, variable, value);
		else
			add_env(shell, variable, value);
		i++;
		g_last_exit_status = 0;
	}
	upd_shell_path(shell);
}
