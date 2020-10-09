/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:20:25 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/09 13:20:32 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** echo
** Prints args after comand separated by space.
** Option -n removes new line in the end of result.
** Option -n is considered only if it is 1st argument.
*/

void	echo(t_shell *shell)
{
	char *args[] = {"-n", "test", NULL};
	if (ft_strcmp(args[0], "-n"))
		ft_printf("%s", args[1]);
	else
		ft_printf("%s\n", args[0]);
}