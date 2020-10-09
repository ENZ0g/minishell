/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:07:15 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/09 20:40:32 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell		*shell;
extern char			**environ;

void			print_tokens(t_token *tokens) //dev
{
	while (tokens)
	{
		write(1, tokens->data, ft_strlen(tokens->data));
		write(1, "\n", 1);
		tokens = tokens->next;
	}
}

void			print_prompt(void) //OK
{
	char	cwd[PATH_MAX];

	if (PATHINPROMPT && getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s $ ", cwd);
	else
		ft_printf("minishell$ ");
}

int			read_line_from_stdin(char **line, int newline) //OK
{
	int			ret;

	ret = 0;
	if (newline)
		print_prompt();
	if ((ret = get_next_line(0, line)) == -1)
		write(1, "\n", 1);
	else if (ret == 1)
		newline = 1;
	else if (ret == 0)
	{
		if (**line != '\0')
			newline = 0;
		else if (**line == '\0' && newline)
		{
			ft_printf("exit\n");
			exit(EXIT_SUCCESS);
		}
	}
	return (newline);
}

