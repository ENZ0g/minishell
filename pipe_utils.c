/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:08:31 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/14 10:55:52 by rhullen          ###   ########.fr       */
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

void	upd_shell_path(t_shell *shell)
{
	int		i;
	char	*temp;

	if (check_env_exist(shell, "PATH="))
	{
		i = 0;
		while (shell->path[i])
		{
			free(shell->path[i]);
			i++;
		}
		free(shell->path);
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
	else
		shell->path[0] = NULL;
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
	shell->cwd = getcwd(NULL, 0);
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

char	*get_prompt(t_shell *shell)
{
	if (PATHINPROMPT)
		return (shell->cwd);
	else
		return (SHELL_PROMPT);
}

void	get_buildin_commands(t_shell *shell)
{
	shell->buildin_commands = (char **)malloc(sizeof(char *) * 8);
	if (!shell->buildin_commands)
		return ;
	shell->buildin_commands[7] = NULL;
	shell->buildin_commands[0] = ft_strdup("echo");
	shell->buildin_commands[1] = ft_strdup("cd");
	shell->buildin_commands[2] = ft_strdup("pwd");
	shell->buildin_commands[3] = ft_strdup("export");
	shell->buildin_commands[4] = ft_strdup("unset");
	shell->buildin_commands[5] = ft_strdup("env");
	shell->buildin_commands[6] = ft_strdup("exit");
}

void	init_shell(t_shell *shell, char **env)
{
	get_shell_path(shell, env);
	get_shell_cwd(shell);
	get_env(shell, env);
	shell->last_exit_status = 0;
	shell->command = 0;
	shell->last_command = 0;
	get_buildin_commands(shell);
	shell->fd_in = dup(0);
	shell->fd_out = dup(1);
}