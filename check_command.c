/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:49:46 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/21 15:37:47 by jnannie          ###   ########.fr       */
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

void			check_correct_command(t_shell *shell, t_command *command, char *data)
{
	int			i;
	struct stat	status_struct;
	char		*total_path;

	if (is_buildin_command(shell, data))
		return ;
	if (data[0] == '.')
	{
		total_path = ft_strjoin(shell->cwd, data + 1);
		if (stat(total_path, &status_struct) == 0 && (status_struct.st_mode & S_IFMT) == S_IFREG)
		{
			command->correct_path = ft_strdup(total_path);
			// command->is_found = 1;
			free(total_path);
			return ;
		}
	}
	if (data[0] == '/')
	{
		if (stat(data, &status_struct) == 0 && (status_struct.st_mode & S_IFMT) == S_IFREG)
		{
			command->correct_path = ft_strdup(data);
			// command->is_found = 1;
			return ;
		}
	}
	command->is_found = 0;
	i = 0;
	while (shell->path[i])
	{
		total_path = ft_strjoin(shell->path[i], data);
		if (stat(total_path, &status_struct) == 0 && (status_struct.st_mode & S_IFMT) == S_IFREG)
		{
			command->correct_path = ft_strdup(total_path);
			command->is_found = 1;
		}
		free(total_path);
		i++;
	}
	if (command->is_found == 0)
		print_error(data, "command not found", 1);
}
