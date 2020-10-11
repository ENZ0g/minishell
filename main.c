/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:18:57 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/11 14:31:29 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		newline = read_line_from_stdin(&shell, &line, newline); // newline?
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

// TODO $HOME
// TODO filter buildin commands (cd, echo)
// TODO ctrl + c when cat running makes double prompt
// TODO when token is empty
// TODO need to clear shell->last_command after ctrl+C