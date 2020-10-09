/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:22:58 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/09 13:30:43 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Print list of env. Like 'env' in bash
*/

void	print_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
		ft_printf("%s\n", shell->env[i++]);
}