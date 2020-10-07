/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 15:45:56 by rhullen           #+#    #+#             */
/*   Updated: 2020/06/07 17:33:47 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_line(char **temp_line, char **line)
{
	char	*temp;
	size_t	i;

	i = 0;
	while ((*temp_line)[i] != '\n')
		if ((*temp_line)[i++] == '\0')
			return (0);
	(*temp_line)[i] = '\0';
	temp = *temp_line;
	*line = ft_strdup(*temp_line);
	*temp_line = ft_strdup(*temp_line + i + 1);
	free(temp);
	temp = NULL;
	return (1);
}

int		read_fd(int fd, char **line, char **temp_line, char *buf)
{
	ssize_t	bytes;
	char	*temp;

	while ((bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		if (*temp_line)
		{
			temp = *temp_line;
			*temp_line = ft_strjoin(*temp_line, buf);
			free(temp);
			temp = NULL;
		}
		else
			*temp_line = ft_strdup(buf);
		if (get_line(temp_line, line))
			break ;
	}
	return (bytes);
}
