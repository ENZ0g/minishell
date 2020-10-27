/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 16:54:40 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/26 00:37:40 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_reg_file(t_shell *shell, t_command *command,
							char *total_path)
{
	if (!(command->correct_path = ft_strdup(total_path)))
	{
		free(total_path);
		exit_shell(shell, EXIT_FAILURE);
	}
	free(total_path);
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
	if (stat(total_path, &status_struct) == 0)
	{
		if ((status_struct.st_mode & S_IFMT) == S_IFREG)
			return (is_reg_file(shell, command, total_path));
		else if ((status_struct.st_mode & S_IFDIR) == S_IFDIR)
			return (2);
	}
	free(total_path);
	return (1);
}

static int		set_if_absolute(t_shell *shell, t_command *command, char *data)
{
	struct stat		status_struct;

	if (stat(data, &status_struct) == 0)
	{
		if ((status_struct.st_mode & S_IFMT) == S_IFREG)
		{
			if (!(command->correct_path = ft_strdup(data)))
				exit_shell(shell, EXIT_FAILURE);
			return (0);
		}
		else if ((status_struct.st_mode & S_IFDIR) == S_IFDIR)
			return (2);
	}
	return (1);
}

static int		check_buildin_abs_rel(t_shell *shell, t_command *command,
									char *data)
{
	int				ret;

	if (is_buildin_command(shell, data))
		return (0);
	ret = 3;
	if (data[0] == '.')
	{
		ret = set_if_relative(shell, command, data);
		if (ret == 1)
			print_error(data, "command not found", 1);
		else if (ret == 2)
			print_error(data, "is a directory", 1);
	}
	if (data[0] == '/')
	{
		ret = set_if_absolute(shell, command, data);
		if (ret == 1)
			print_error(data, "command not found", 1);
		else if (ret == 2)
			print_error(data, "is a directory", 1);
	}
	return (ret);
}

int				prepath_check(t_shell *shell, t_command *command, char *data)
{
	int		ret;

	if (!(ret = check_buildin_abs_rel(shell, command, data)))
	{
		command->is_found = 1;
		return (1);
	}
	else if (ret == 1 || ret == 2)
	{
		if (ret == 1)
			g_last_exit_status = 127;
		else
			g_last_exit_status = 126;
		return (1);
	}
	return (0);
}
