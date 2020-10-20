/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:27:43 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/20 21:23:30 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fatal_error(void)
{
	ft_printf_error("minishell: %s\n", strerror(errno));
	total_free();
	exit(1);
}

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
	while (str[len] && str[len] != '=')
		len++;
	len++;
	var_name = (char *)malloc(sizeof(char) * (len + 1));
	if (!var_name)
		fatal_error();
	var_name[len--] = '\0';
	var_name[len--] = '=';
	i = 0;
	while (len-- >= 0)
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
	char	*var_value;
	char	*ptr;
	char	*temp;

	ptr = ft_strchr(str, '=');
	if (ptr == NULL)
		return (ft_strdup(""));
	ptr++;
	len = 0;
	temp = ptr;
	while (*ptr++)
		len++;
	var_value = (char *)malloc(sizeof(char) * (len + 1));
	if (!var_value)
		fatal_error();
	var_value[len--] = '\0';
	i = 0;
	while (len-- >= 0)
	{
		var_value[i] = *temp++;
		i++;
	}
	return (var_value);
}
