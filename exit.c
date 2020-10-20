/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:20:04 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/20 21:10:26 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ft_isnum
** Checks that str consists only from digit chars.
*/

int		ft_isnum(char *str)
{
	if (str)
	{
		while (*str)
		{
			if (!ft_isdigit(*str))
				return (0);
			str++;
		}
	}
	return (1);
}

void	nested_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	total_free(void)
{
	free(shell->path);
	free(shell->cwd);
	free(shell->last_command);
	nested_free(shell->buildin_commands);
	nested_free(shell->env);
}

/*
** close_shell
** Frees dynamically allocated memory and exits from minishell.
** Like 'exit' in bash.
*/

void	close_shell(t_shell *shell)
{
	if (!ft_isnum(shell->command->argv[1]))
	{
		ft_printf_error("exit\nminishell: exit: %s: numeric argument "\
						"required\n", shell->command->argv[1]);
		total_free();
		exit(-1);
	}
	if (ft_arraylen(shell->command->argv) > 2)
	{
		ft_printf_error("exit\nminishell: exit: too many arguments\n");
		shell->last_exit_status = 1;
	}
	else
	{
		total_free();
		ft_printf_error("exit\n");
		exit(ft_atoi(shell->command->argv[1]));
	}
}
