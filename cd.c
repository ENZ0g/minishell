/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:19:42 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/13 11:05:36 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** cd
** Like 'cd' in bash
*/

void	cd(t_shell *shell, char** args)
{
	char	*temp_cwd;

	temp_cwd = getcwd(NULL, 0);
	if (chdir(args[1]) == -1)
		ft_printf("minishell: cd: %s: %s\n", args[1], strerror(errno));
	upd_env(shell, ft_strdup("PWD="), getcwd(NULL, 0));
	shell->cwd = getcwd(NULL, 0);
	upd_env(shell, ft_strdup("OLDPWD="), temp_cwd);
}