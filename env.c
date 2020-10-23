/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:22:58 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/21 15:42:06 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Print list of environment variables. Like 'env' in bash
*/

void	print_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
		ft_printf("%s\n", shell->env[i++]);
	g_last_exit_status = 0;
}
