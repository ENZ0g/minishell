/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 14:02:25 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/24 17:27:29 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		wait_for_process(void)
{
	int			pid;
	int			exit_status;

	if ((pid = waitpid(-1, &exit_status, 0)) == -1)
		return (-1);
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
		exit_status = exit_status | 128;
	if (g_last_pid == pid)
		g_last_exit_status = exit_status;
	g_child_pid_count--;
	return (exit_status);
}

int		set_fd_in(t_shell *shell, t_command *command)
{
	int		fd_in;

	if (shell->command->input_file_name)
		fd_in = command->file_fd_in;
	else if (shell->fd_pipe[0])
		fd_in = dup(shell->fd_pipe[0]);
	else
		fd_in = dup(shell->fd_stdin);
	if (shell->fd_pipe[0])
		close(shell->fd_pipe[0]);
	shell->fd_pipe[0] = 0;
	return (fd_in);
}

int		set_fd_out(t_shell *shell, t_command *command)
{
	int		fd_out;

	fd_out = 0;
	if (command->is_pipe)
	{
		if (pipe(shell->fd_pipe) == -1)
			exit_shell(shell, EXIT_FAILURE);
		fd_out = dup(shell->fd_pipe[1]);
	}
	if (shell->command->out_file_name)
	{
		if (fd_out)
			close(fd_out);
		fd_out = command->file_fd_out;
	}
	else if (!command->is_pipe)
		fd_out = dup(shell->fd_stdout);
	if (shell->fd_pipe[1])
		close(shell->fd_pipe[1]);
	shell->fd_pipe[1] = 0;
	return (fd_out);
}

void	child_process(t_shell *shell, t_command *command)
{
	if (shell->fd_pipe[0])
		close(shell->fd_pipe[0]);
	if (is_buildin_command(shell, command->argv[0]))
	{
		run_buildin(shell, command);
		exit_shell(shell, 0);
	}
	else
	{
		execve(command->correct_path, command->argv, shell->env);
		errno = 0;
		exit_shell(shell, 127);
	}
}

void	parent_process(t_shell *shell, int pid)
{
	g_child_pid_count++;
	dup2(shell->fd_stdin, 0);
	dup2(shell->fd_stdout, 1);
	g_last_pid = pid;
	while (g_child_pid_count)
		wait_for_process();
	g_child_pid_count = 0;
}
