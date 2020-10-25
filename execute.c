/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:31:12 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/25 12:30:58 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			pwd(char *cwd)
{
	ft_printf("%s\n", cwd);
}

int			run_buildin(t_shell *shell, t_command *command)
{
	if (ft_strcmp(command->argv[0], "echo"))
		echo(command->argv);
	// else if (ft_strcmp(command->argv[0], "cd"))
	// 	cd(shell, command->argv);
	else if (ft_strcmp(command->argv[0], "pwd"))
		pwd(shell->cwd);
	// else if (ft_strcmp(command->argv[0], "export"))
	// 	export(shell, command);
	// else if (ft_strcmp(command->argv[0], "unset"))
	// 	unset(shell, command);
	else if (ft_strcmp(command->argv[0], "env"))
		print_env(shell);
	// else if (ft_strcmp(command->argv[0], "exit"))
	// 	close_shell(shell);
	else
		return (0);
	return (1);
}

static int		exec_buildins_if_no_pipe(t_shell *shell, t_command *command)
{
	if (command->is_pipe == 0)
	{
		if (ft_strcmp(command->argv[0], "export"))
		{
			export(shell, command);
			return (1);
		}
		else if (ft_strcmp(command->argv[0], "unset"))
		{
			unset(shell, command);
			return (1);
		}
		else if (ft_strcmp(command->argv[0], "exit"))
		{
			close_shell(shell);
			return (1);
		}
		else if (ft_strcmp(command->argv[0], "cd"))
		{
			cd(shell, command->argv);
			return (1);
		}
	}
	return (0);
}

void			execute(t_shell *shell, t_command *command)
{
	int			fd_in;
	int			fd_out;
	int			pid;

	if (exec_buildins_if_no_pipe(shell, command))
		return ;
	fd_in = set_fd_in(shell, command);
	fd_out = set_fd_out(shell, command);
	dup2(fd_in, 0);
	close(fd_in);
	dup2(fd_out, 1);
	close(fd_out);
	if (!run_buildin(shell, command))
	{
		pid = fork();
		if (pid == -1)
			exit_shell(shell, EXIT_FAILURE);
		if (pid == 0)
			child_process(shell, command);
	}
	if (!command->is_pipe)
		parent_process(shell, pid);
	// else
	// 	g_child_pid_count++;
}
