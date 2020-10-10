/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:18:57 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/10 11:26:57 by jnannie          ###   ########.fr       */
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
		line = 0;
		newline = read_line_from_stdin(&line, newline); // newline?
		if ((tokens = parse_line(line)) &&
			(shell.pipe = parse_tokens(&shell, tokens)))
			line = 0;
			// execute(&shell);
		free(line);
		// print_tokens(tokens); //dev
		print_pipes(&shell); //dev
		free_pipes(&shell);
		free_tokens(tokens);
	}
	return (0);
}


//TODO no such comand error
//TODO new lines when ENTER