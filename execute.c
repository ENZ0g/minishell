/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:31:12 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/12 20:33:21 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_buildin(t_shell *shell, t_command *command)
{
	int	i;

	i = 0;
	// printf("pwd - .%s.\n", command->argv[0]);
	while (shell->buildin_commands[i])
	{
		if (ft_strcmp(command->argv[0], "echo")) // +
		{
			echo(command->argv);
			return ;
		}
		else if (ft_strcmp(command->argv[0], "cd"))
		{
			echo(command->argv); //
			return ;
		}
		else if (ft_strcmp(command->argv[0], "pwd")) // +
		{
			// printf("pwd - %s\n", command->argv[0]);
			ft_printf("%s\n", shell->cwd);
			return ;
		}
		else if (ft_strcmp(command->argv[0], "export")) // +
		{
			printf("in export branch\n");
			export(shell, command);
			return ;
		}
		else if (ft_strcmp(command->argv[0], "unset")) // +
		{
			unset(shell, command);
			return ;
		}
		else if (ft_strcmp(command->argv[0], "env")) // +
		{
			print_env(shell);
			return ;
		}
		else if (ft_strcmp(command->argv[0], "exit")) // +
			close_shell(shell);
		i++;
	}
}

void	execute(t_shell *shell)
{
	int			temp_in;
	int			temp_out;
	int			fd_in;
	int			fd_out;
	int			pid;
	t_pipe		*pipeline;
	int			fd[2];
	int			exit_status;
	t_command	*command;

	pipeline = shell->pipe;
	while (pipeline)
	{
		temp_in = dup(0);
		temp_out = dup(1);
		if (pipeline->is_input_from_file)	//this block to pipeline cycle
		{
			fd_in = open(pipeline->input_file_name, O_RDONLY);
			if (fd_in == -1)
			{
				ft_printf("minishell: %s\n", strerror(errno));
				return ;
			}
		}
		else
			fd_in = dup(temp_in);
		command = pipeline->command;
		while (command)
		{
			if (pipeline->is_pipe == 0)
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
			}
			dup2(fd_in, 0);
			close(fd_in);

			if (command->next == NULL) // last comand
			{
				if (pipeline->is_out_in_file)
				{
					if (pipeline->is_append)
						fd_out = open(pipeline->out_file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
					else
						fd_out = open(pipeline->out_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
					if (fd_out == -1)
					{
						ft_printf("minishell: %s\n", strerror(errno));
						return ;
					}
				}
				else
					fd_out = dup(temp_out);
			}
			else // not last comand
			{
				if (pipe(fd) == -1)
				{
					ft_printf("minishell: %s\n", strerror(errno));
					return ;
				}
				fd_in = fd[0];
				fd_out = fd[1];
			}
			dup2(fd_out, 1);
			close(fd_out);
			// print_argv(command->argv);
			// printf("path - %s\n", command->correct_path);
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
				// if build in -> run command
				if (is_buildin_command(shell, command->argv[0]))
				{
					printf("run buildin\n");
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
		pipeline = pipeline->next;
	}
	
}