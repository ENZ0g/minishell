/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:21:01 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/12 20:27:09 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** unset
** Removes variables from env list.
*/

void	unset(t_shell *shell, t_command *command)
{
	int		i;

	i = 0;
	while (command->argv[i])
	{
		if (check_env_exist(shell, command->argv[i]))
			remove_env(shell, command->argv[i]);
		i++;	
	}
}