/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:18:57 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/19 02:03:28 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*shell;

int		main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_token		*tokens;
	// t_shell		shell;
	char		*temp_line;

	if (argc != 1)
	{
		ft_printf("%s need not arguments!\n", argv[0]);
		return (1);
	}
	if (!(shell = init_shell(envp)))
		exit (EXIT_FAILURE);
	set_signals_handlers();
	while (1)
	{
		shell->command = 0; //?
		tokens = 0;
		line = 0;
		// shell.fd_stdin = dup(0);
		// shell.fd_stdout = dup(1);
		// if (!shell->sigint_flag && !TEST)
		if (!shell->sigint_flag && !TEST)
			print_prompt();
		shell->sigint_flag = 0;
		if (read_line_from_stdin(&line) == -1) // newline?
		{
			free(line);
			continue ;
		}
		// if (sigint_flag)
		// {
		// 	free(shell.last_command);
		// 	shell.last_command = 0;
		// 	sigint_flag = 0;
		// }
		// if (newline && shell.last_command)
		// {
		// 	free(line);
		// 	line = ft_strdup(shell.last_command); //strjoin(line, shell.last_command)
		// 	free(shell.last_command);
		// 	shell.last_command = 0;
		// }
		temp_line = line;
		line = skip_whitespaces(line);
		line = ft_strdup(line);
		free(temp_line);
		if (*line && (tokens = parse_line(line)))
		{
			if (check_tokens(shell, tokens) == 0)		// we need to know beforehand if there is something like "echo hello ; echo 123 ; ;" so we set shell->parsing_error
				while (tokens && !shell->parsing_error)
				{
					tokens = parse_tokens(shell, tokens);
					if (shell->command->argv && !shell->parsing_error)	// this parsing_error is set if quotes are not enclosed, if ambiguous redirect (echo > $DKFSL), or if No such file or directory
						execute(shell);
					free(shell->command);		//free_command() to free args and everything
					shell->parsing_error = 0;
					dup2(shell->fd_stdin, 0);
					dup2(shell->fd_stdout, 1);
					// if (!tokens)
					// 	break ;
				}
			else
				free_tokens(tokens);
			shell->parsing_error = 0;
		}
		// dup2(shell->fd_stdin, 0);
		// dup2(shell->fd_stdout, 1);


		// print_commands(&shell);
		free(line);
		// print_tokens(tokens); //dev
		// print_pipes(&shell); //dev
		// free_tokens(tokens);
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

// cat < TEST should not work ?? in bash it work
// bash-3.2$ echo dfs > $KDJFK
// bash: $KDJFK: ambiguous redirect
// $DKSFJ -> seg fault

// echo hello | fds |eiwry | | -> should print error and 

// if enter just space -> command not found

// echo hello > $DKFJ test

// $DKF echo hello

// echo 123; $DKFJ -> seg fault

// why we moved command existence check from execution?

// catch signals from programs when ctrl c or ctrl \

// double prompt when ctrl c from cat
// ctrl d works only first time


// commands below should work simultaneously, not one by one
// cat | echo hello
// cat | cat
// cat | grep

// cat ; cat ; cat // should not print prompt with ctrl c

// make shell not global again

// echo "echo hello" | bash // it is doubtful that it can be implemented

// return status codes when we call minishell from minishell

// cat | echo hello -> in bash exits after first entered line, in minishell not
// cat | cat | echo 123

// echo hello ; cat > $DSKF
// echo hello | cat > $DSKF
// echo hello ; cat > $DSKF
// echo hello ; cat > |
// echo hello ; cat > $DKSFL;  echo 123

// maybe set "^\Quit: 3" for child processes