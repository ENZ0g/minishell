/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:31:12 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/09 20:10:34 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	temp_in = dup(0); 
	temp_out = dup(1);
	if (shell->pipe->is_input_from_file)
	{
		fd_in = open(shell->pipe->input_file_name, O_RDONLY);
		if (fd_in == -1)
		{
			ft_printf("minishell: %s\n", strerror(errno));
			return ;
		}
	}
	else
		fd_in = dup(temp_in);
	pipeline = shell->pipe;
	while (pipeline)
	{
		dup2(fd_in, 0);
		close(fd_in);

		if (pipeline->next == NULL) // last comand
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
		pid = fork();
		if (pid == -1)
		{
			ft_printf("minishell: %s\n", strerror(errno));
			return ;
		}
		if (pid == 0)
			execve(pipeline->correct_path, pipeline->command->argv, shell->env);
		pipeline = pipeline->next;
	}
	dup2(temp_in, 0);
	dup2(temp_out, 1);
	close(temp_in);
	close(temp_out);
	wait(&exit_status);
	if (WIFEXITED(exit_status))
		shell->last_exit_status = WEXITSTATUS(exit_status);
}