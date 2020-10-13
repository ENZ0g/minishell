/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:07:15 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/13 17:34:50 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell		*shell;
extern char			**environ;

void			print_tokens(t_token *tokens) //dev
{
	printf("tockens:\n");
	while (tokens)
	{
		write(1, tokens->data, ft_strlen(tokens->data));
		write(1, "\n", 1);
		tokens = tokens->next;
	}
}

void		print_argv(char **argv) //dev
{
	//printf("print args\n");
	if (!argv || !*argv || !**argv)
		return ;
	while (argv && *argv)
	{
		write(1, *argv, ft_strlen(*argv));
		if (**argv)
			write(1, " ", 1);
		argv++;
	}
	write(1, "\n", 1);
}

void			print_commands(t_shell *shell) //dev
{
	t_command	*command;

	command = shell->command;
	while (command)
	{
		if (command->input_file_name)
		{
			write(1, "input file is: ", 15);
			write(1, command->input_file_name, ft_strlen(command->input_file_name));
			write(1, "\n", 1);
		}
		if (command->out_file_name)
		{
			write(1, "output file is: ", 16);
			write(1, command->out_file_name, ft_strlen(command->out_file_name));
			write(1, "\n", 1);
		}
		print_argv(command->argv);
		command = command->next;
	}
}

void			print_prompt(void) //OK
{
	char	cwd[PATH_MAX];

	if (PATHINPROMPT && getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s $ ", cwd);
	else
		ft_printf(SHELL_PROMPT);
}

int			read_line_from_stdin(t_shell *shell, char **line, int newline) //OK
{
	int			ret;

	ret = 0;
	if ((ret = get_next_line(0, line)) == -1)
	{
		write(1, "\n", 1);
		newline = 1;
	}
	else if (ret == 1)
		newline = 1;
	else if (ret == 0)
	{
		if (sigint_flag)
			newline = 1;
		if (**line != '\0')
		{
			if (shell->last_command)
				free(shell->last_command);
			shell->last_command = ft_strdup(*line);
			newline = 0;
		}
		else if (**line == '\0' && newline)
		{
			ft_printf("exit\n");
			exit(EXIT_SUCCESS);
		}
	}
	return (newline);
}
