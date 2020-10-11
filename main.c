/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:18:57 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/11 20:23:04 by jnannie          ###   ########.fr       */
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
		tokens = 0;
		line = 0;
		if (newline)
			print_prompt();
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
			line = ft_strdup(shell.last_command);
			free(shell.last_command);
			shell.last_command = 0;
		}
		if (line && *line && newline &&
			(tokens = parse_line(line)) &&
			(shell.pipe = parse_tokens(&shell, tokens)))
		{
			// print_pipes(&shell);
			execute(&shell);
		}
		free(line);
		// print_tokens(tokens); //dev
		// print_pipes(&shell); //dev
		free_pipes(&shell);
		free_tokens(tokens);
	}
	return (0);
}

// TODO $HOME | done
// TODO filter buildin commands (cd, echo)
// TODO ctrl + c when cat running makes double prompt | decision in the line below
// TODO need to set some global flag flag when ctrl+C to clear shell->last_command and not to print prompt | temporary added sigint_flag variable
// TODO free shell before exit
// should error messages go to stdout or stderror?
// in parse_tokens we pass &shell and then return shell.pipe, that does not make sense
// what for shell->parsing_error? and maybe it sould be initialized every cycle, and need to be set in parse functions
// doesnt execute with full path /Users/jnannie/Desktop/mini/minishell
// should not run program in current directory with "minishell", only with "./minishell"
// when command not found should set last_exit_status to 127 | done
