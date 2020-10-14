/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:09:34 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/14 20:07:51 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_command(void)
{
	t_command	*new;

	new = (t_command *)ft_calloc(1, sizeof(t_command));
	return (new);
}

t_command	*get_last_command(t_command *comands)
{
	t_command	*last;

	last = comands;
	while (last->next)
		last = last->next;
	return (last);
}

void		command_add_back(t_command *comands, t_command *new)
{
	t_command *last;

	if (comands->next == NULL)
	{
		comands->next = new;
		return ;
	}
	last = get_last_command(comands);
	last->next = new;
}
