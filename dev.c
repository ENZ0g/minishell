/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:27:24 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/20 19:36:42 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	printf("tockens:\n");
	while (tokens)
	{
		write(1, tokens->data, ft_strlen(tokens->data));
		write(1, "\n", 1);
		tokens = tokens->next;
	}
}

void	print_argv(char **argv)
{
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

// void	print_commands(t_shell *shell)
// {
// 	t_command	*command;

// 	command = shell->command;
// 	while (command)
// 	{
// 		if (command->input_file_name)
// 		{
// 			write(1, "input file is: ", 15);
// 			write(1, command->input_file_name,
// 					ft_strlen(command->input_file_name));
// 			write(1, "\n", 1);
// 		}
// 		if (command->out_file_name)
// 		{
// 			write(1, "output file is: ", 16);
// 			write(1, command->out_file_name,
// 					ft_strlen(command->out_file_name));
// 			write(1, "\n", 1);
// 		}
// 		print_argv(command->argv);
// 		command = command->next;
// 	}
// }
