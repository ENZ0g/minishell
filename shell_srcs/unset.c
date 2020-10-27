/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:21:01 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/26 14:27:48 by jnannie          ###   ########.fr       */
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

	i = 1;
	while (command->argv[i])
	{
		if (!is_unset_name_valid(command->argv[i]))
		{
			ft_printf_error("minishell: unset: `%s': not a valid "\
							"identifier\n", command->argv[i]);
			g_last_exit_status = 1;
			return ;
		}
		if (check_env_exist(shell, command->argv[i]))
			remove_env(shell, command->argv[i]);
		i++;
	}
	upd_shell_path(shell);
}
