/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 16:54:40 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/25 17:00:35 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			command_is_found(t_shell *shell, t_command *command,
								char *total_path)
{
	if (!(command->correct_path = ft_strdup(total_path)))
	{
		free(total_path);
		exit_shell(shell, EXIT_FAILURE);
	}
	command->is_found = 1;
}
