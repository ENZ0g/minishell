#include <stdio.h>
#include "libft.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

typedef struct	s_shell
{
	char		**path;
	short		out_in_file; // 0 -> 1
	short		append; // 0 -> 1
	short		in_from_file; // 0 -> 1
	short		pipe;
	char		*out_file_name; 
	char		*in_file_name;
	short		is_found;
	char		**args;
	char		*correct_path;
	char		*cwd;
	short		comands_count;
}				t_shell;

void	init_shell(t_shell *shell)
{
	shell->out_in_file = 0;
	shell->is_found = 0;
	shell->in_from_file = 0;
	shell->append = 0;
	shell->pipe = 0;
	shell->comands_count = 0;
}

char	*get_from_env(char *to_find, char **env)
{
	int		i;
	size_t	len;

	len = ft_strlen(to_find);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], to_find, len) == 0)
			return (env[i]);
		i++;
	}
	return (0);
}

void	get_path(t_shell *shell, char **env)
{
	int		i;
	char	*temp;

	shell->path = ft_split(get_from_env("PATH=", env) + 5, ':');
	shell->cwd = ft_strdup(get_from_env("PWD=", env) + 4);
	i = 0;
	while (shell->path[i])
	{
		temp = shell->path[i];
		shell->path[i] = ft_strjoin(shell->path[i], "/");
		free(temp);
		i++;
	}
	temp = shell->cwd;
	shell->cwd = ft_strjoin(shell->cwd, "/");
	free(temp);
}

void	print_path_dev(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->path[i])
	{
		printf("path: %s\n", shell->path[i]);
		i++;
	}
}

void	get_args(t_shell *shell, char *comand)
{
	shell->args = ft_split(comand, ' ');
}

void	parse_for_redirect(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->args[i])
	{
		if (ft_strcmp(shell->args[i], ">") && shell->args[i + 1])
		{
			shell->out_in_file = 1;
			shell->out_file_name = shell->args[i + 1];
			shell->args[i] = NULL;
			break ;
		}
		else if (ft_strcmp(shell->args[i], ">>") && shell->args[i + 1])
		{
			shell->out_in_file = 1;
			shell->append = 1;
			shell->out_file_name = shell->args[i + 1];
			shell->args[i] = NULL;
			break ;
		}
		if (ft_strcmp(shell->args[i], "<") && shell->args[i + 1])
		{
			shell->in_from_file = 1;
			shell->in_file_name = shell->args[i + 1];
			shell->args[i] = NULL;
			break ;
		}
		if (ft_strcmp(shell->args[i], "|"))
		{
			shell->pipe = 1;
			break ;
		}
		i++;
	}
}

void	get_correct_path(t_shell *shell)
{
	int			i;
	char		*total_path;
	struct stat status_struct;

	i = 0;
	while (shell->path[i])
	{
		total_path = ft_strjoin(shell->path[i], shell->args[0]);
		if (stat(total_path, &status_struct) == 0)
		{
			shell->correct_path = ft_strdup(total_path);
			printf("correct path - %s\n", shell->correct_path);
			shell->is_found = 1;
		}
		free(total_path);
		i++;
	}
	if (!shell->is_found)
	{
		total_path = ft_strjoin(shell->cwd, shell->args[0]);
		if (stat(total_path, &status_struct) == 0)
			shell->correct_path = ft_strdup(total_path);
		else
			printf("minishell: comand not found: %s\n", shell->args[0]);
		free(total_path);
	}
}

int     main(int argc, char **argv, char **env)
{
    char    *comand;
    int     pid;
	int		fd_out;
	int		fd_in;
	t_shell	shell;

	if (argc > 1)
	{
		ft_printf("%s: No arguments are needed!\n", argv[0] + 2);
		return (1);
	}
	// ft_printf("minishell is launched\n");
	while (1)
	{
		init_shell(&shell);
		get_path(&shell, env);
		// print_path_dev(&shell); // dev
		
		ft_printf("minishell $ ");
		if (get_next_line(0, &comand) && *comand)
		{
			get_args(&shell, comand);
			parse_for_redirect(&shell);
			get_correct_path(&shell);
			pid = fork();
			if (pid == -1)
				printf("Fork comand fail\n");
			if (pid == 0) // child
			{
				if (shell.out_in_file) // send output to file (> or >>)
				{ 
					if (shell.append) // (>>)
						fd_out = open(shell.out_file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
					else // (>)
						fd_out = open(shell.out_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
					if (fd_out == -1)
					{
						printf("minishell: %s: %s\n", strerror(errno), shell.in_file_name);
						exit(-1);
					}
					else
					{
						dup2(fd_out, STDOUT_FILENO);
						close(fd_out);
					}
				}
				if (shell.in_from_file) // get input from file (<)
				{
					fd_in = open(shell.in_file_name, O_RDONLY);
					if (fd_in == -1)
					{
						printf("minishell: %s: %s\n", strerror(errno), shell.in_file_name);
						exit(-1);
					}
					else
					{
						dup2(fd_in, 0);
						close(fd_in);
					}
				}
				execve(shell.correct_path, shell.args, env);
			}
			else // parent
				wait(NULL);
		}
		free(comand);
	}
    return (0);
}


// int	fd[2];
// if (pipe(fd) == -1) // fd[0] - read, fd[1] - write
// 	// error //


// sampels of pipe comands:
// ls | wc -l
// cat pipe_test.txt | head -7 | tail -1