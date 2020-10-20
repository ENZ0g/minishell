/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:21:01 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/20 21:33:42 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_unset_name_valid(char *name)
{
	if (!ft_isalpha(*name++))
		return (0);
	while (*name)
	{
		if (*name != '_' && !ft_isalnum(*name))
			return (0);
		name++;
	}
	return (1);
}

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
		if (!is_unset_name_valid(command->argv[i]))
		{
			ft_printf_error("minishell: unset: `%s': not a valid "\
							"identifier\n", command->argv[i]);
			return ;
		}
		if (check_env_exist(shell, command->argv[i]))
			remove_env(shell, command->argv[i]);
		i++;
	}
	upd_shell_path(shell);
}
