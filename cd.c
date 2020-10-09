/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:19:42 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/09 13:19:46 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** cd
** Like 'cd' in bash
*/

void	cd(t_shell *shell)
{
	char	*temp_cwd;
	char	*test[] = { "../cub3d", NULL };

	temp_cwd = getcwd(NULL, 0); // need to be freed
	if (chdir(test[0]) == -1)
		ft_printf("minishell: cd: %s: %s\n", test[0], strerror(errno));
	upd_env(shell, "PWD=", getcwd(NULL, 0));
	upd_env(shell, "OLDPWD=", temp_cwd);
}