/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:49:46 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/23 01:01:02 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_buildin_command(t_shell *shell, char *command)
{
	int	i;

	i = 0;
	while (shell->buildin_commands[i])
	{
		if (ft_strcmp(command, shell->buildin_commands[i]))
			return (1);
		i++;
	}
	return (0);
}

static int		set_if_relative(t_shell *shell, t_command *command, char *data)
{
	struct stat		status_struct;
	char			*total_path;
	char			*temp;

	if (!(total_path = ft_strjoin(shell->cwd, "/")))
		exit_shell(shell, EXIT_FAILURE);
	temp = total_path;
	total_path = ft_strjoin(total_path, data);
	free(temp);
	if (!(total_path))
		exit_shell(shell, EXIT_FAILURE);
	if (stat(total_path, &status_struct) == 0 &&
		(status_struct.st_mode & S_IFMT) == S_IFREG)
	{
		if (!(command->correct_path = ft_strdup(total_path)))
		{
			free(total_path);
			exit_shell(shell, EXIT_FAILURE);
		}
		free(total_path);
		return (1);
	}
	free(total_path);
	return (0);
}

static int		set_if_absolute(t_shell *shell, t_command *command, char *data)
{
	struct stat		status_struct;

	if (stat(data, &status_struct) == 0 &&
		(status_struct.st_mode & S_IFMT) == S_IFREG)
	{
		if (!(command->correct_path = ft_strdup(data)))
			exit_shell(shell, EXIT_FAILURE);
		return (1);
	}
	return (0);
}

static int		check_buildin_abs_rel(t_shell *shell, t_command *command,
									char *data)
{
	if (is_buildin_command(shell, data))
		return (1);
	if (data[0] == '.')
	{
		if (!set_if_relative(shell, command, data))
			print_error(data, "command not found", 1);
		return (1);
	}
	if (data[0] == '/')
	{
		if (!set_if_absolute(shell, command, data))
			print_error(data, "command not found", 1);
		return (1);
	}
	return (0);
}

void			check_correct_command(t_shell *shell, t_command *command,
									char *data)
{
	int				i;
	struct stat		status_struct;
	char			*total_path;

	if (check_buildin_abs_rel(shell, command, data))
		return ;
	i = 0;
	while (shell->path[i])
	{
		if (!(total_path = ft_strjoin(shell->path[i++], data)))
			exit_shell(shell, EXIT_FAILURE);
		if (stat(total_path, &status_struct) == 0 &&
			(status_struct.st_mode & S_IFMT) == S_IFREG)
		{
			if (!(command->correct_path = ft_strdup(total_path)))
			{
				free(total_path);
				exit_shell(shell, EXIT_FAILURE);
			}
			command->is_found = 1;
		}
		free(total_path);
	}
	if (command->is_found == 0)
		print_error(data, "command not found", 1);
}
