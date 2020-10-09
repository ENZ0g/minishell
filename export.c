/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:18:46 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/09 13:19:12 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** export
** Sets new env variable.
** Upds variable's value if variable is in env list.
** Adds variable with its value if variable is not in env list.
*/

void	export(t_shell *shell) // export
{
	char	*test[2] = { "EXPORT1=2", NULL };
	int		i;	
	char	*variable;
	char	*value;

	i = 0;
	while (test[i])
	{
		variable = get_var_name(test[i]); // need to be freed
		value = get_var_value(test[i]); // need to be freed
		if (check_env_exist(shell, variable))
			upd_env(shell, variable, value);
		else
			add_env(shell, variable, value);
		i++;
	}
}