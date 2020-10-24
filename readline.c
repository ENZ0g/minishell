/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:07:15 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/24 13:47:32 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		shell_get_line(t_shell *shell, char **temp_line,
							char **line, char *buf)
{
	size_t		i;

	i = 0;
	while ((*temp_line)[i] != '\n')
		if ((*temp_line)[i++] == '\0')
			return (0);
	(*temp_line)[i] = '\0';
	if (!(*line = ft_strdup(*temp_line)))
	{
		free(*temp_line);
		free(buf);
		exit_shell(shell, EXIT_FAILURE);
	}
	free(*temp_line);
	*temp_line = NULL;
	return (1);
}

void	join_buf(t_shell *shell, char **temp_line, char *buf)
{
	char		*temp;

	temp = *temp_line;
	if (!(*temp_line = ft_strjoin(*temp_line, buf)))
	{
		free(temp);
		free(buf);
		exit_shell(shell, EXIT_FAILURE);
	}
	free(temp);
}

int		shell_read_fd(t_shell *shell, char **line,
								char **temp_line, char *buf)
{
	ssize_t		bytes;

	while ((bytes = read(0, buf, BUFFER_SIZE)) >= 0)
	{
		if (g_sigint_flag)
		{
			free(*temp_line);
			*temp_line = NULL;
			g_sigint_flag = 0;
		}
		buf[bytes] = '\0';
		if (bytes == 0 && !*temp_line)
		{
			free(buf);
			!TEST ? write(2, "exit\n", 5) : 0;
			exit_shell(shell, EXIT_SUCCESS);
		}
		if (*temp_line)
			join_buf(shell, temp_line, buf);
		else if (!(*temp_line = ft_strdup(buf)))
			return (-1);
		if (shell_get_line(shell, temp_line, line, buf))
			break ;
	}
	return (bytes);
}

int		shell_gnl(t_shell *shell, char **line)
{
	char			*buf;
	static char		*temp_line;
	int				status;

	if (!line)
		return (-1);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (temp_line)
		if (shell_get_line(shell, &temp_line, line, buf))
		{
			free(buf);
			return (1);
		}
	if ((status = shell_read_fd(shell, line, &temp_line, buf)) == -1)
	{
		free(buf);
		return (-1);
	}
	free(buf);
	if (status)
		return (1);
	*line = temp_line;
	temp_line = NULL;
	return (0);
}

int		read_line_from_stdin(t_shell *shell, char **line)
{
	if (shell_gnl(shell, line) == -1)
	{
		write(2, "get_next_line() error\n", 22);
		return (-1);
	}
	return (0);
}
