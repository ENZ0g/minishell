/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:18:46 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/13 19:34:18 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** export
** Sets new env variable.
** Upds variable's value if variable is in env list.
** Adds variable with its value if variable is not in env list.
*/

void	export(t_shell *shell, t_command *command)
{
	//char	*test[2] = { "EXPORT1=2", NULL };
	int		i;	
	char	*variable;
	char	*value;

	i = 1;
	while (command->argv[i])
	{
		if (!ft_isalpha(command->argv[i][0]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(command->argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			shell->last_exit_status = 1;
			return ;
		}
		variable = get_var_name(command->argv[i]); // need to be freed
		value = get_var_value(command->argv[i]); // need to be freed
		if (check_env_exist(shell, variable))
			upd_env(shell, variable, value);
		else
			add_env(shell, variable, value);
		i++;
	}
	upd_shell_path(shell);
	shell->last_exit_status = 0;
}