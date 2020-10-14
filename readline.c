/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:07:15 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/14 20:29:10 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	char	cwd[PATH_MAX];

	if (PATHINPROMPT && getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s $ ", cwd);
	else
		ft_printf(SHELL_PROMPT);
}

int		read_line_from_stdin(t_shell *shell, char **line, int newline)
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
			if (!TEST)
				ft_printf("exit\n");
			exit(EXIT_SUCCESS);
		}
	}
	return (newline);
}
