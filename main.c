/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:18:57 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/12 20:56:32 by rhullen          ###   ########.fr       */
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
		shell.pipe = 0;
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
			(parse_tokens(&shell, tokens) == 0))
		{
			// print_pipes(&shell);
			execute(&shell);
		}
		free(line);
		// print_tokens(tokens); //dev
		// print_pipes(&shell); //dev
		free_tokens(tokens);
		free_pipes(&shell);
	}
	return (0);
}

// TODO cd
// TODO free shell before exit
// should error messages go to stdout or stderror?
// TODO signals


