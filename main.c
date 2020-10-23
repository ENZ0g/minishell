/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:18:57 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/23 11:39:25 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_shell	*shell;
int				g_sigint_flag = 0;
int				g_last_pid = 0;
int				g_last_exit_status = 0;
int				g_child_pid_count = 0;

void			nested_free(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void			free_command(t_shell *shell)
{
	if (!shell->command)
		return ;
	free(shell->command->correct_path);
	nested_free(shell->command->argv);
	// shell->command->argv = 0;
	free(shell->command->out_file_name);
	free(shell->command->input_file_name);
	free(shell->command);
	shell->command = 0;
}

int				main(int argc, char *argv[], char *envp[])
{
	// char		*line;
	t_token		*tokens;
	char		*temp_line;
	t_shell		*shell;

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
		shell->tokens = 0;
		shell->line = 0;
		if (g_sigint_flag != 1 && !TEST)
			print_prompt();
		g_sigint_flag = 0;
		if (read_line_from_stdin(shell, &shell->line) == -1)
			exit_shell(shell, EXIT_FAILURE);
		temp_line = shell->line;
		shell->line = skip_whitespaces(shell->line);
		if (!(shell->line = ft_strdup(shell->line)))
		{
			free(temp_line);
			exit_shell(shell, EXIT_FAILURE);
		}
		free(temp_line);
		if (*shell->line && (shell->tokens = parse_line(shell, shell->line)))
		{
			tokens = shell->tokens;
			if ((check_tokens(shell, tokens)))		// we need to know beforehand if there is something like "echo hello ; echo 123 ; ;" so we set shell->parsing_error
				while (tokens && !shell->parsing_error)
				{
					tokens = parse_tokens(shell, tokens);
					if (shell->command->argv && !shell->parsing_error)	// this parsing_error is set if quotes are not enclosed, if ambiguous redirect (echo > $DKFSL), or if No such file or directory
						execute(shell, shell->command);
					// free(shell->last_var);
					// shell->last_var = 0;
					free_command(shell);
					shell->parsing_error = 0;
					dup2(shell->fd_stdin, 0);
					dup2(shell->fd_stdout, 1);
				}
			free_tokens(shell);
			shell->parsing_error = 0;
		}
		free(shell->line);
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

// check_tokens

// Exit the shell with a status of N.  If N is omitted, the exit status
//    is that of the last command executed.

// if No such file or directory the g_last_exit_status = 1

// echo hello > $DFLKJ$FDJK

// if echo $HOME and then echo dkfj > $DFL -> minishell: $HOME$DFL: ambiguous redirect

// echo $HOME > $DFK -> minishell: $HOME$DFK: ambiguous redirect

// ../minishell doesnt work