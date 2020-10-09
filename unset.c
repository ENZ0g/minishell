/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:21:01 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/09 13:21:08 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** unset
** Removes variables from env list.
*/

void	unset(t_shell *shell)
{
	char	*test[] = { "EXPORT1", "test", NULL };
	int		i;

	i = 0;
	while (test[i])
	{
		if (check_env_exist(shell, test[i]))
			remove_env(shell, test[i]);		
	}
}