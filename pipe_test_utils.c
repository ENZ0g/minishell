/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_test_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:08:31 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/10 11:10:09 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_from_env(char *to_find, char **env)
{
	int		i;
	size_t	len;

	len = ft_strlen(to_find);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], to_find, len) == 0)
			return (env[i]);
		i++;
	}
	return (0);
}

void	get_shell_path(t_shell *shell, char **env)
{
	int		i;
	char	*temp;

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

void	get_shell_cwd(t_shell *shell)
{
	char	*temp;

	shell->cwd = getcwd(NULL, 0);
	temp = shell->cwd;
	shell->cwd = ft_strjoin(shell->cwd, "/");
	free(temp);
}

int		get_array_len(char **array)
{
	int	len;

	len = 0;
	while (*array++)
		len++;
	return len;
}

void	get_env(t_shell *shell, char **env)
{
	int		env_len;
	char	**new_env;
	int		i;

	env_len = get_array_len(env);
	new_env = (char **)(malloc(sizeof(char *) * (env_len + 1)));
	if (!new_env)
		return ; // ???
	new_env[env_len] = NULL;
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	shell->env = new_env;
	shell->env_len = env_len;
}

void	init_shell(t_shell *shell, char **env)
{
	get_shell_path(shell, env);
	get_shell_cwd(shell);
	get_env(shell, env);
	shell->last_exit_status = 0;
	shell->pipe = 0;
}