/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:27:43 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/09 14:28:44 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** get_var_name
** Returns string content before first '=' character with '=' character.
*/

char	*get_var_name(char *str)
{
	int		len;
	int		i;
	char	*var_name;

	len = 0;
	while (str[len] != '=')
		len++;
	len++;
	var_name = (char *)malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return NULL;
	var_name[len--] = '\0';
	var_name[len--] = '=';
	i = 0;
	while (i < len)
	{
		var_name[i] = str[i];
		i++;
	}
	return (var_name);
}

/*
** get_var_value
** Returns string content after first '=' character.
*/

char	*get_var_value(char *str)
{
	int		len;
	int		i;
	char	*var_name;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	len = 0;
	while (str[i])
		len++;
	var_name = (char *)malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return NULL;
	var_name[len--] = '\0';
	i = 0;
	while (i < len)
	{
		var_name[i] = str[i];
		i++;
	}
	return (var_name);
}