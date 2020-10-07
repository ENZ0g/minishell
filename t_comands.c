/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_comands.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:09:34 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/07 13:11:17 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_comands	*new_comand(void)
{
	t_comands	*new;

	new = (t_comands *)ft_calloc(1, sizeof(t_comands));
	return (new);
}

t_comands	*get_last_comand(t_comands *comands)
{
	t_comands	*last;

	last = comands;
	while (last->next)
		last = last->next;
	return (last);
}

void		comand_add_back(t_comands *comands, t_comands *new)
{
	t_comands *last;

	if (comands->next == NULL)
	{
		comands->next = new;
		return ;
	}
	last = get_last_comand(comands);
	last->next = new;
}