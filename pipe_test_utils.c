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

void	get_shell_cwd(t_shell *shell, char **env)
{
	char	*temp;

	shell->cwd = getcwd(NULL, 0);
	temp = shell->cwd;
	shell->cwd = ft_strjoin(shell->cwd, "/");
	free(temp);
}

void	init_shell(t_shell *shell, char **env)
{
	get_shell_path(shell, env);
	get_shell_cwd(shell, env);
}