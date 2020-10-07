/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 14:45:58 by rhullen           #+#    #+#             */
/*   Updated: 2020/05/11 20:54:02 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*result;

	if (!lst || !f)
		return (0);
	result = 0;
	while (lst)
	{
		if ((temp = ft_lstnew(f(lst->content))))
		{
			ft_lstadd_back(&result, temp);
			lst = lst->next;
		}
		else
		{
			ft_lstclear(&result, del);
			return (0);
		}
	}
	return (result);
}
