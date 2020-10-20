/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:18:57 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/20 16:02:54 by jnannie          ###   ########.fr       */
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
	// int			fd[2];

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
		// shell->pid = 0;

		// pipe(fd);
		// printf("%d %d\n", fd[0], fd[1]);
		// close(fd[0]);
		// close(fd[1]);

		// shell.fd_stdin = dup(0);
		// shell.fd_stdout = dup(1);
		// if (!shell->sigint_flag && !TEST)
		if (shell->sigint_flag != 1 && !TEST)
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
					// shell->tokens = tokens;
					if (shell->command->argv && !shell->parsing_error)	// this parsing_error is set if quotes are not enclosed, if ambiguous redirect (echo > $DKFSL), or if No such file or directory
						execute(shell);
					free(shell->command);		//free_command() to free args and everything
					shell->parsing_error = 0;
					dup2(shell->fd_stdin, 0);
					dup2(shell->fd_stdout, 1);
					// pipe(fd);
					// printf("%d %d\n", fd[0], fd[1]);
					// printf("%d %d\n", shell->fd_stdin, shell->fd_stdout);
					// close(fd[0]);
					// close(fd[1]);
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

// make shell not global again // do not make shell not global again

// echo "echo hello" | bash // it is doubtful that it can be implemented

// cat | echo hello -> in bash exits after first entered line, in minishell not
// cat | cat | echo 123

// echo hello ; cat > $DSKF
// echo hello | cat > $DSKF
// echo hello ; cat > $DSKF
// echo hello ; cat > |
// echo hello ; cat > $DKSFL;  echo 123

// maybe set "^\Quit: 3" for child processes

// try something like echo hello > test | cat

// return status codes when we call minishell from minishell

// cat ; cat ; cat // should not print prompt with ctrl c

// cat;cat;cat;

// ls -> ctrl d -> ctrl c -> ctrl \ -> then if enter text it will be added to "ls"

// $>
// bash: syntax error near unexpected token `newline'
// bash-3.2$ $?
// bash: 258: command not found

// after cat | cat |cat and ctrl c last status stay 130 and does not change