/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:31:12 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/13 21:51:22 by rhullen          ###   ########.fr       */
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
	int			temp_in;
	int			temp_out;
	int			fd_in;
	int			fd_out;
	int			pid;
	int			fd[2];
	int			exit_status;
	t_command	*command;

	temp_in = dup(0);
	temp_out = dup(1);
	command = shell->command;
	while (command)
	{
		puts("-------------------");
		printf("is_found - %d\n", command->is_found);
		printf("correct path - %s\n", command->correct_path);
		int i = 0;
		while (command->argv[i])
		{
			printf("arg %d - %s\n", i, command->argv[i]);
			i++;
		}
		printf("is out in file - %d\n", command->is_out_in_file);
		printf("out file name - %s\n", command->out_file_name);
		printf("is append - %d\n", command->is_append);
		printf("is input from file - %d\n", command->is_input_from_file);
		printf("in file name - %s\n", command->input_file_name);
		printf("is pipe - %d\n", command->is_pipe);
		printf("next - %p\n", command->next);
		puts("-------------------");
		
		if (command->is_pipe == 0)
		{
			if (ft_strcmp(command->argv[0], "export")) // +
			{
				export(shell, command);
				break ;
			}
			else if (ft_strcmp(command->argv[0], "unset")) // +
			{
				unset(shell, command);
				break ;
			}
			else if (ft_strcmp(command->argv[0], "exit")) // +
			{
				close_shell(shell);
				break ;
			}
			else if (ft_strcmp(command->argv[0], "cd")) // +
			{
				cd(shell, command->argv);
				break ;
			}
		}
		
		
		fd_in = temp_in;
		fd_out = temp_out;

		if (command->is_pipe)
		{
			if (pipe(fd) == -1)
			{
				ft_printf("minishell: %s\n", strerror(errno));
				return ;
			}
			close(fd_in);
			close(fd_out);
			fd_in = fd[0];
			fd_out = fd[1];
		}

		if (command->is_input_from_file)	//this block to pipeline cycle
		{
			close(fd_in);
			fd_in = open(command->input_file_name, O_RDONLY); // try chmod -rwx
			if (fd_in == -1)
			{
				ft_printf("minishell: %s\n", strerror(errno));
				return ;
			}
		}
			
		if (command->is_out_in_file)
		{
			close(fd_out);
			if (command->is_append)
				fd_out = open(command->out_file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
			else
				fd_out = open(command->out_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd_out == -1)
			{
				ft_printf("minishell: %s\n", strerror(errno));
				return ;
			}
		}

		dup2(fd_in, 0);
		close(fd_in);
		dup2(fd_out, 1);
		close(fd_out);

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
		else
		{
			wait(&exit_status);
			if (WIFEXITED(exit_status))
				shell->last_exit_status = WEXITSTATUS(exit_status);		
		}
		command = command->next;
	}
	dup2(temp_in, 0);
	dup2(temp_out, 1);
	close(temp_in);
	close(temp_out);
}