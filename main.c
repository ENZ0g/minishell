/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:18:57 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/24 15:17:15 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				g_sigint_flag = 0;
int				g_last_pid = 0;
int				g_last_exit_status = 0;
int				g_child_pid_count = 0;

static t_shell	*preset_main(int argc, char **argv, char **envp)
{
	t_shell		*shell;

	if (argc != 1)
	{
		print_error(argv[0], "there must not be arguments!", 1);
		exit(EXIT_FAILURE);
	}
	if (!(shell = init_shell(envp)))
		exit_shell(shell, EXIT_FAILURE);
	set_signals_handlers();
	return (shell);
}

static void		parse_and_execute(t_shell *shell)
{
	t_token		*tokens;

	if (*shell->line && (shell->tokens = parse_line(shell, shell->line)))
	{
		tokens = shell->tokens;
		if ((check_tokens(shell, tokens)))
			while (tokens && !shell->parsing_error)
			{
				tokens = parse_tokens(shell, tokens);
				if (shell->command->argv && !shell->parsing_error)
					execute(shell, shell->command);
				free_command(shell);
				shell->parsing_error = 0;
				dup2(shell->fd_stdin, 0);
				dup2(shell->fd_stdout, 1);
			}
		free_tokens(shell);
		shell->parsing_error = 0;
	}
}

static void		skip_whitespaces_in_line(t_shell *shell)
{
	char		*temp_line;

	temp_line = shell->line;
	shell->line = skip_whitespaces(shell->line);
	if (!(shell->line = ft_strdup(shell->line)))
	{
		free(temp_line);
		exit_shell(shell, EXIT_FAILURE);
	}
	free(temp_line);
}

int				main(int argc, char *argv[], char *envp[])
{
	t_shell		*shell;

	shell = preset_main(argc, argv, envp);
	while (1)
	{
		shell->command = 0;
		shell->tokens = 0;
		shell->line = 0;
		if (g_sigint_flag != 1 && !TEST)
			print_prompt();
		g_sigint_flag = 0;
		if (read_line_from_stdin(shell, &shell->line) == -1)
			exit_shell(shell, EXIT_FAILURE);
		skip_whitespaces_in_line(shell);
		parse_and_execute(shell);
		free(shell->line);
	}
	return (0);
}
