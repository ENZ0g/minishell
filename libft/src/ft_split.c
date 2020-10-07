/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:03:16 by rhullen           #+#    #+#             */
/*   Updated: 2020/05/19 21:40:50 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_tokens(const char *s, char sep)
{
	size_t		counter;

	if (!s || *s == '\0')
		return (0);
	counter = 0;
	while (*s)
	{
		while (*s == sep && *s)
			s++;
		if (*s)
			counter++;
		while (*s != sep && *s)
			s++;
	}
	return (counter);
}

static char		**del_result(char **result)
{
	size_t	i;

	i = 0;
	while (result[i])
		free(result[i++]);
	free(result);
	result = NULL;
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	size_t	counter;
	size_t	i;
	size_t	len;

	counter = count_tokens(s, c);
	if (!(result = (char **)ft_calloc((counter + 1), sizeof(char *))))
		return (NULL);
	if (!counter)
		return (result);
	i = 0;
	while (i < counter)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			s++;
			len++;
		}
		if (!(result[i++] = ft_substr(s - len, 0, len)))
			return (del_result(result));
	}
	return (result);
}
