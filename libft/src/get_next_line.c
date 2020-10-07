/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:03:08 by rhullen           #+#    #+#             */
/*   Updated: 2020/06/07 21:56:35 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*temp_line;
	int			status;

	if (!line || (fd < 0 || fd >= MAX_FD))
		return (-1);
	if (temp_line)
		if (get_line(&temp_line, line))
			return (1);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if ((status = read_fd(fd, line, &temp_line, buf)) == -1)
		return (-1);
	free(buf);
	if (temp_line == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	if (status)
		return (1);
	*line = temp_line;
	temp_line = NULL;
	return (0);
}
