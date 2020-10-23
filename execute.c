/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:31:12 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/23 14:04:58 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			pwd(char *cwd)
{
	ft_printf("%s\n", cwd);
}

void			run_buildin(t_shell *shell, t_command *command)
{
	int	i;

	i = 0;
	while (shell->buildin_commands[i])
	{
		if (ft_strcmp(command->argv[0], "echo"))
			return (echo(command->argv));
		else if (ft_strcmp(command->argv[0], "cd"))
			return (cd(shell, command->argv));
		else if (ft_strcmp(command->argv[0], "pwd"))
			return (pwd(shell->cwd));
		else if (ft_strcmp(command->argv[0], "export"))
			return (export(shell, command));
		else if (ft_strcmp(command->argv[0], "unset"))
			return (unset(shell, command));
		else if (ft_strcmp(command->argv[0], "env"))
			return (print_env(shell));
		else if (ft_strcmp(command->argv[0], "exit"))
			return (close_shell(shell));
		i++;
	}
}

int				wait_for_process(void)
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

static int		set_fd_in(t_shell *shell, t_command *command)
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

static int		set_fd_out(t_shell *shell, t_command *command)
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

static void		child_process(t_shell *shell, t_command *command)
{
	if (shell->fd_pipe[0])
		close(shell->fd_pipe[0]);
	if (is_buildin_command(shell, command->argv[0]))
	{
		run_buildin(shell, command);
		exit(0);
	}
	else
	{
		execve(command->correct_path, command->argv, shell->env);
		exit(127);
	}
}

static void		parent_process(t_shell *shell, int pid)
{
	g_child_pid_count++;
	dup2(shell->fd_stdin, 0);
	dup2(shell->fd_stdout, 1);
	g_last_pid = pid;
	while (g_child_pid_count)
		wait_for_process();
	g_child_pid_count = 0;
}

void			execute(t_shell *shell, t_command	*command)
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
	pid = fork();
	if (pid == -1)
		exit_shell(shell, EXIT_FAILURE);
	if (pid == 0)
		child_process(shell, command);
	else if (!command->is_pipe)
		parent_process(shell, pid);
	else
		g_child_pid_count++;
}