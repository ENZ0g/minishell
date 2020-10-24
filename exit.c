/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:20:04 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/24 13:33:58 by rhullen          ###   ########.fr       */
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
		exit_shell(shell, EXIT_FAILURE);
	}
	if (ft_arraylen(shell->command->argv) > 2)
	{
		ft_printf_error("exit\nminishell: exit: too many arguments\n");
		g_last_exit_status = 1;
	}
	else
	{
		ft_printf_error("exit\n");
		exit_shell(shell, ft_atoi(shell->command->argv[1]));
	}
}
