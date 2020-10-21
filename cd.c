/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:19:42 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/21 15:41:31 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_shell *shell, char **args)
{
	char	*temp_cwd;

	temp_cwd = getcwd(NULL, 0);
	if (chdir(args[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		g_last_exit_status = 1;
	}
	upd_env(shell, ft_strdup("PWD="), getcwd(NULL, 0));
	shell->cwd = getcwd(NULL, 0);
	upd_env(shell, ft_strdup("OLDPWD="), temp_cwd);
}
