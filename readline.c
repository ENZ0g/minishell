/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:07:15 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/24 00:02:04 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_prompt(void)
{
	char	cwd[PATH_MAX];

	if (PATHINPROMPT && getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s $ ", cwd);
	else
		ft_printf(SHELL_PROMPT);
}

static int		shell_get_line(t_shell *shell, char **temp_line,
							char **line, char *buf)
{
	size_t	i;

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

static void		join_buf(t_shell *shell, char **temp_line, char *buf)
{
	char	*temp;

	{
		temp = *temp_line;
		if (!(*temp_line = ft_strjoin(*temp_line, buf)))
		{
			free(temp);
			free(buf);
			exit_shell(shell, EXIT_FAILURE);
		}
		free(temp);
	}
}

static int		shell_read_fd(t_shell *shell, int fd, char **line,
								char **temp_line, char *buf)
{
	ssize_t	bytes;

	while ((bytes = read(fd, buf, BUFFER_SIZE)) >= 0)
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
			if (!TEST)
				write(2, "exit\n", 5);
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

static int			shell_gnl(t_shell *shell, int fd, char **line)
{
	char		*buf;
	static char	*temp_line;
	int			status;

	if (!line || (fd < 0 || fd >= MAX_FD))
		return (-1);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (temp_line)
		if (shell_get_line(shell, &temp_line, line, buf))
		{
			free(buf);
			return (1);
		}
	if ((status = shell_read_fd(shell, fd, line, &temp_line, buf)) == -1)
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

int				read_line_from_stdin(t_shell *shell, char **line)
{
	if (shell_gnl(shell, 0, line) == -1)
	{
		write(2, "get_next_line() error\n", 22);
		return (-1);
	}
	return (0);
}
