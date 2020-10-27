/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 19:53:32 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/26 15:12:15 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	upd_shell_path(t_shell *shell)
{
	int		i;
	char	*temp;

	if (check_env_exist(shell, "PATH="))
	{
		nested_free(shell->path);
		shell->path = ft_split(get_from_env("PATH=", shell->env) + 5, ':');
		i = 0;
		while (shell->path[i])
		{
			temp = shell->path[i];
			shell->path[i] = ft_strjoin(shell->path[i], "/");
			free(temp);
			i++;
		}
	}
	else if (shell->path)
	{
		nested_free(shell->path);
		shell->path = (char **)(malloc(sizeof(char *) * 1));
		if (!shell->path)
			exit_shell(shell, EXIT_FAILURE);
		shell->path[0] = NULL;
	}
}

void	get_shell_path(t_shell *shell, char **env)
{
	int		i;
	char	*temp;

	if (check_env_exist(shell, "PATH"))
	{
		shell->path = ft_split(get_from_env("PATH=", env) + 5, ':');
		i = 0;
		while (shell->path[i])
		{
			temp = shell->path[i];
			shell->path[i] = ft_strjoin(shell->path[i], "/");
			free(temp);
			i++;
		}
	}
	else
	{
		shell->path = (char **)(malloc(sizeof(char *) * 1));
		if (!shell->path)
			exit_shell(shell, EXIT_FAILURE);
		shell->path[0] = NULL;
	}
}

void	get_shell_cwd(t_shell *shell)
{
	shell->cwd = getcwd(NULL, 0);
}

int		get_array_len(char **array)
{
	int	len;

	len = 0;
	while (*array++)
		len++;
	return (len);
}

char	*get_prompt(t_shell *shell)
{
	if (PATHINPROMPT)
		return (shell->cwd);
	else
		return (SHELL_PROMPT);
}
