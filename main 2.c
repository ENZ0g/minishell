/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:07:15 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/09 17:04:13 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/syslimits.h>
#include "minishell.h"

extern t_shell		*shell;
extern char			**environ;

static void			print_tokens(t_token *tokens)
{
	while (tokens)
	{
		write(1, tokens->data, ft_strlen(tokens->data));
		write(1, "\n", 1);
		tokens = tokens->next;
	}
}

static void			print_prompt(void)
{
	char	cwd[PATH_MAX];

	errno = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_printf("%s $ ", cwd);
	}
	else
	{
		perror("getcwd() error");
		ft_printf(" $ ");
	}
}

// static int			run_command(const char *filename, char *const argv[],
// 							char *const envp[])
// {
// 	pid_t pid;
// 	int status;

// 	pid = fork();

// 	if (pid == -1)
// 	{
// 		return (-1);
// 	}
// 	else if (pid > 0)
// 	{
// 		waitpid(pid, &status, 0);
// 	}
// 	else
// 	{
// 		execve(filename, argv, envp);
// 		exit(EXIT_FAILURE);
// 	}
// 	return (0);
// }

static int			execute_commands(t_pipe *pipe)
{
	pipe = 0;
	return ((int)pipe);
}

void				quit_handler(int signum)
{
	write(1, "\b\b  \b\b", 6);
	(void)signum;
}

void				int_handler(int signum)
{
	write(1, "\b\b  \b\b", 6);
	ft_printf("\n");
	print_prompt();
	(void)signum;
}

void				set_signals_handlers(void)
{
	signal(SIGQUIT, quit_handler);
	signal(SIGINT, int_handler);
}

// static void			tty_setup(char *envp[])
// {
// 	//stty -echoctl
// 	pid_t		pid;
// 	int			status;
// 	char		*argv;

// 	argv = "-echoctl";
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		execve("/bin/stty", &argv, envp);
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid > 0)
// 	{
// 		wait(&status);
// 	}
// 	else
// 	{
// 		perror("fork failed");
// 		exit(EXIT_FAILURE);
// 	}
// }

static int			read_line_from_stdin(char **line, int newline)
{
	int			ret;

	ret = 0;
	if (newline)
		print_prompt();
	if ((ret = get_next_line(0, line)) == -1)
		write(1, "\n", 1);
	else if (ret == 1)
		newline = 1;
	else if (ret == 0)
	{
		if (**line != '\0')
			newline = 0;
		else if (**line == '\0' && newline)
		{
			ft_printf("exit\n");
			exit(EXIT_SUCCESS);
		}
	}
	return (newline);
}

// static t_pipe		*create_commands(t_token *tokens)
// {
// 	tokens = 0;
// 	return ((t_pipe *)tokens);
// }

t_shell				*shell_init(void)
{
	shell = ft_calloc(1, sizeof(t_shell));
	shell->pipe = ft_calloc(1, sizeof(t_pipe));
	shell->pipe->command = ft_calloc(1, sizeof(t_command));
	shell->env = environ;
	return (shell);
}

int					main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_token		*tokens;
	int			newline;
	// t_shell		*shell;

	shell = shell_init();
	set_signals_handlers();
	newline = 1;
	while (1)
	{
		line = 0;
		newline = read_line_from_stdin(&line, newline);
		if ((tokens = parse_line(line)) &&
			(shell->pipe = parse_tokens(tokens)))
			execute_commands(shell->pipe);
		free(line);
		print_tokens(tokens);
		free_tokens(tokens);
	}

	return (argc && (void **)argv && (void **)envp);
}
