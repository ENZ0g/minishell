#include "minishell.h"

void	execute(t_shell *shell, char **env)
{
	int			temp_in;
	int			temp_out;
	int			fd_in;
	int			fd_out;
	int			pid;
	t_comands	*comand;
	int			fd[2];

	temp_in = dup(0); 
	temp_out = dup(1);
	if (shell->comands->is_input_from_file)
	{
		fd_in = open(shell->comands->input_file_name, O_RDONLY);
		if (fd_in == -1)
		{
			ft_printf("minishell: %s\n", strerror(errno));
			return ;
		}
	}
	else
		fd_in = dup(temp_in);
	comand = shell->comands;
	while (comand)
	{
		dup2(fd_in, 0);
		close(fd_in);

		if (comand->next == NULL) // last comand
		{
			if (comand->is_out_in_file)
			{
				if (comand->is_append)
					fd_out = open(comand->out_file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
				else
					fd_out = open(comand->out_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
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
			execve(comand->correct_path, comand->args, env);
		comand = comand->next;
	}
	dup2(temp_in, 0);
	dup2(temp_out, 1);
	close(temp_in);
	close(temp_out);
	wait(NULL);
}

int     main(int argc, char **argv, char **env)
{
	t_shell	shell;

	init_shell(&shell, env);
	// cat pipe_test.txt | head -7 | tail -1
	char	*args1[] = {"/cat", "pipe_test.txt", NULL};
	char	*args2[] = {"/grep", "Pipe", NULL};
	char	*args3[] = {"/grep", "two", NULL};

	// cat
	shell.comands = new_comand();
	shell.comands->args = args1;
	shell.comands->correct_path = "/bin/cat";

	// head
	shell.comands->next = new_comand();
	shell.comands->next->args = args2;
	shell.comands->next->correct_path = "/usr/bin/grep";

	// tail
	shell.comands->next = new_comand();
	shell.comands->next->args = args3;
	shell.comands->next->correct_path = "/usr/bin/grep";

	execute(&shell, env);
	printf("something after exec\n");
	return (0);
}