/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:19:42 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/23 23:56:26 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_shell *shell, char **args)
{
	char	*temp_cwd;

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
