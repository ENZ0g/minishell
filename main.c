/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:18:57 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/15 22:55:32 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sigint_flag = 0;

int		main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_token		*tokens;
	int			newline;
	t_shell		shell;
	t_command	*command;

	if (argc != 1)
	{
		ft_printf("%s need not arguments!\n", argv[0]);
		return (1);
	}
	init_shell(&shell, envp);
	set_signals_handlers();
	newline = 1;
	while (1)
	{
		shell.command = 0; //?
		tokens = 0;
		line = 0;
		if (newline && !sigint_flag && !TEST)
			print_prompt();
		sigint_flag = 0;
		newline = read_line_from_stdin(&shell, &line, newline); // newline?
		if (sigint_flag)
		{
			free(shell.last_command);
			shell.last_command = 0;
			sigint_flag = 0;
		}
		if (newline && shell.last_command)
		{
			free(line);
			line = ft_strdup(shell.last_command); //strjoin(line, shell.last_command)
			free(shell.last_command);
			shell.last_command = 0;
		}
		if (*line && newline)
		{
			tokens = parse_line(line);
			while ((command = parse_tokens(&shell, tokens)))
			{
				execute(&shell, command);
				free(command);
			}
		}
		dup2(shell.fd_stdin, 0);
		close(shell.fd_stdin);
		dup2(shell.fd_stdout, 1);
		close(shell.fd_stdout);
		print_commands(&shell);
		free(line);
		// print_tokens(tokens); //dev
		// print_pipes(&shell); //dev
		free_tokens(tokens);
	}
	return (0);
}

// TODO free shell before exit
// should error messages go to stdout or stderror?
// macros??
// ls ctr D -> ctr C pwd == lspwd
// echo "rews\d" -> \ should stay
// mkdir test\ test -> should make dir test_test (with space)
// unset $KJADHFLKDSJ -> nothing (newline) ; cat $KDFJS the same
// echo test123 > 123.t > t.t -> 123.t not created

// bash-3.2$ cat < t.t < test.txt
// bash: t.t: No such file or directory
// bash-3.2$ cat < test.txt < t.t
// bash: t.t: No such file or directory

// redirections in pipes does not work wellq

// ERRORS when malloc or fork or open fails
// ls | grep sig | cat >test

// cat < TEST should not work
// echo hello | cat |cat| cat
// bash-3.2$ echo dfs > $KDJFK
// bash: $KDJFK: ambiguous redirect
