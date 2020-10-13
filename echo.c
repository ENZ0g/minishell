/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:20:25 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/13 11:29:39 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** echo
** Prints args after comand separated by space.
** Option -n removes new line in the end of result.
** Option -n is considered only if it is 1st argument.
*/

void	echo(char **args)
{
	int i;
	int	new_line;

	if (args[1] == NULL)
	{
		ft_printf("\n");
		return ;
	}
	new_line = 1;
	i = 1;
	if (ft_strcmp(args[1], "-n"))
	{
		i = 2;
		new_line = 0;
	}
	while (args[i])
	{
		if (args[i + 1] == NULL)
			ft_printf("%s", args[i]);
		else
			ft_printf("%s ", args[i]);
		i++;
	}
	if (new_line)
		ft_printf("\n");
}