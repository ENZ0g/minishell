/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:18:46 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/14 20:25:29 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** export
** Sets new env variable.
** Upds variable's value if variable is in env list.
** Adds variable with its value if variable is not in env list.
*/

void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	export(t_shell *shell, t_command *command)
{
	int		i;
	char	*variable;
	char	*value;

	i = 1;
	while (command->argv[i])
	{
		if (!ft_isalpha(command->argv[i][0]))
		{
			print_export_error(command->argv[i]);
			shell->last_exit_status = 1;
			i++;
			continue ;
		}
		variable = get_var_name(command->argv[i]);
		value = get_var_value(command->argv[i]);
		if (check_env_exist(shell, variable))
			upd_env(shell, variable, value);
		else
			add_env(shell, variable, value);
		i++;
	}
	upd_shell_path(shell);
	shell->last_exit_status = 0;
}
