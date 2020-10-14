/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:21:01 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/14 20:07:08 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** unset
** Removes variables from environment list.
*/

void	unset(t_shell *shell, t_command *command)
{
	int		i;

	i = 0;
	while (command->argv[i])
	{
		if (!ft_isalpha(command->argv[i][0]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(command->argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return ;
		}
		if (check_env_exist(shell, command->argv[i]))
			remove_env(shell, command->argv[i]);
		i++;
	}
	upd_shell_path(shell);
}
