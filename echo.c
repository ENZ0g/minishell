/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:20:25 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/09 20:39:50 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** echo
** Prints args after comand separated by space.
** Option -n removes new line in the end of result.
** Option -n is considered only if it is 1st argument.
*/

void	echo(char **args) // TODO loop through args!
{
	if (ft_strcmp(args[1], "-n"))
		ft_printf("%s", args[2]);
	else
		ft_printf("%s\n", args[1]);
}