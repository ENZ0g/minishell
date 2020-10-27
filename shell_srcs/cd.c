/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:19:42 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/26 14:16:47 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_shell *shell, char **args)
{
	char	*temp_cwd;

	g_last_exit_status = 0;
	if (!args[1])
		return ;
	temp_cwd = getcwd(NULL, 0);
	if (chdir(args[1]) == -1)
	{
		ft_printf_error("minishell: cd: %s: %s\n", args[1], strerror(errno));
		g_last_exit_status = 1;
	}
	upd_env(shell, ft_strdup("PWD="), getcwd(NULL, 0));
	shell->cwd = getcwd(NULL, 0);
	upd_env(shell, ft_strdup("OLDPWD="), temp_cwd);
}
