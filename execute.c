/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:31:12 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/19 01:26:11 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char *cwd)
{
	ft_printf("%s\n", cwd);
}

void	run_buildin(t_shell *shell, t_command *command)
{
	int	i;

	i = 0;
	while (shell->buildin_commands[i])
	{
		if (ft_strcmp(command->argv[0], "echo"))
			return (echo(shell, command->argv));
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

// read -stdin - 0 | write -stdout - 1
//
// if pipe -> pipe()
// if redirect in -> open -> read = FD ; close pipe(read)
// if redirect out-> open -> out = FD ; close pipe(write)
// 
//
// before exec dup2()

void	execute(t_shell *shell)
{
	int			fd_in;
	int			fd_out;
	int			pid;
	// int			fd[2];
	int			exit_status;
	t_command	*command;
	// int			temp_fdin;

	// fd[0] = dup(0);
	// fd[1] = dup(1);
	// puts("-------------------");
	// printf("is_found - %d\n", command->is_found);
	// printf("correct path - %s\n", command->correct_path);
	// int i = 0;
	// while (command->argv[i])
	// {
	// 	printf("arg %d - %s\n", i, command->argv[i]);
	// 	i++;
	// }
	// printf("is out in file - %d\n", command->is_out_in_file);
	// printf("out file name - %s\n", command->out_file_name);
	// printf("is append - %d\n", command->is_append);
	// printf("is input from file - %d\n", command->is_input_from_file);
	// printf("in file name - %s\n", command->input_file_name);
	// printf("is pipe - %d\n", command->is_pipe);
	// printf("next - %p\n", command->next);
	// puts("-------------------");
	
	command = shell->command;
	if (command->is_pipe == 0)
	{
		if (ft_strcmp(command->argv[0], "export")) // +
		{
			export(shell, command);
			return ;
		}
		else if (ft_strcmp(command->argv[0], "unset")) // +
		{
			unset(shell, command);
			return ;
		}
		else if (ft_strcmp(command->argv[0], "exit")) // +
		{
			close_shell(shell);
			return ;
		}
		else if (ft_strcmp(command->argv[0], "cd")) // +
		{
			cd(shell, command->argv);
			return ;
		}
	}

	// fd_in = dup(fd[0]);
	// fd_out = dup(fd[1]);
	// close(fd[0]);
	// close(fd[1]);

	if (command->is_input_from_file)	//this block to pipeline cycle
	{
		// close(fd_in);
		fd_in = command->file_fd_in;
	}
	else if (shell->fd_pipe[0])
	{
		fd_in = dup(shell->fd_pipe[0]);
	}
	else
	{
		fd_in = dup(shell->fd_stdin);
	}

	if (shell->fd_pipe[0])
		close(shell->fd_pipe[0]);
	shell->fd_pipe[0] = 0;

	if (command->is_out_in_file)
	{
		fd_out = command->file_fd_out;
	}
	else if (command->is_pipe)
	{
		if (pipe(shell->fd_pipe) == -1)
		{
			ft_printf("minishell: %s\n", strerror(errno));
			return ;
		}
		// close(shell->fd_out);
		fd_out = shell->fd_pipe[1];
		shell->fd_pipe[1] = 0;
	}
	else
	{
		// close(shell->fd_out);
		fd_out = dup(shell->fd_stdout);
	}

	// printf("%d\n", shell->fd_pipe[0]);
	// printf("%d\n", shell->fd_pipe[1]);

	// printf("%d\n", temp_fdin);
	dup2(fd_in, 0);
	close(fd_in);
	dup2(fd_out, 1);
	close(fd_out);

	// if (command->is_pipe)
	// 	shell->fd_in = fd[0];
	// else
	// 	shell->fd_in = dup(shell->fd_stdin);

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	if (pid == 0)
	{
		if (shell->fd_pipe[0])
			close(shell->fd_pipe[0]);
		// printf("%d\n\n\n", temp_fdin);
		// close(shell->fd_pipe[0]);
		// signal(SIGPIPE, sigpipe_handler);
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
	else if (!command->is_pipe)
	{
		dup2(shell->fd_stdin, 0);		// it needs for "cat | echo hello" to work like in bash
		dup2(shell->fd_stdout, 1);
		while (shell->child_pid_count--)
		{
			wait(&exit_status);
			if (WIFEXITED(exit_status))
				shell->last_exit_status = WEXITSTATUS(exit_status);
			else if (WIFSIGNALED(exit_status))
			{
				shell->last_exit_status = exit_status | 128;
				// if (WTERMSIG(exit_status) == SIGQUIT)
				// 	shell->last_exit_status = 131;
				// else if (WTERMSIG(exit_status) == SIGINT)
				// 	shell->last_exit_status = 130;
				// else if (WTERMSIG(exit_status) == SIGPIPE)
				// {
				// 	printf("%d\n", exit_status);
				// 	shell->last_exit_status = 141;
				// }
			}
		// dup2(shell->fd_stdin, 0);
		// dup2(shell->fd_stdout, 1);
		// pipe(shell->fd_pipe);
		
		// 	printf("%d %d\n", shell->fd_pipe[0], shell->fd_pipe[1]);
		// 	close(shell->fd_pipe[0]);
		// 	close(shell->fd_pipe[1]);
		}
		shell->child_pid_count = 1;
	}
	else
	{
		shell->child_pid_count++;
	}
	// dup2(shell->fd_in, 0);
	// dup2(shell->fd_out, 1);
}