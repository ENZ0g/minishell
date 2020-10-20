/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:07:15 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/20 17:49:38 by jnannie          ###   ########.fr       */
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

static int		shell_get_line(char **temp_line, char **line)
{
	// char	*temp;
	size_t	i;

	i = 0;
	while ((*temp_line)[i] != '\n')
		if ((*temp_line)[i++] == '\0')
			return (0);
	(*temp_line)[i] = '\0';
	// temp = *temp_line;
	*line = ft_strdup(*temp_line);
	// *temp_line = ft_strdup(*temp_line + i + 1);
	free(*temp_line);
	*temp_line = NULL;
	// temp = NULL;
	return (1);
}

static int		shell_read_fd(int fd, char **line, char **temp_line, char *buf)
{
	ssize_t	bytes;
	char	*temp;

	while ((bytes = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		if (shell->sigint_flag)
		{
			free(*temp_line);
			*temp_line = NULL;
			shell->sigint_flag = 0;
			// return (0);
		}
		buf[bytes] = '\0';
		if (bytes == 0 && !*temp_line)
		{
			ft_printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		if (*temp_line)
		{
			temp = *temp_line;
			*temp_line = ft_strjoin(*temp_line, buf);
			free(temp);
			temp = NULL;
		}
		else
			*temp_line = ft_strdup(buf);
		if (shell_get_line(temp_line, line))
			break ;
	}
	return (bytes);
}

static int			shell_gnl(int fd, char **line)
{
	char		*buf;
	static char	*temp_line;
	int			status;

	if (!line || (fd < 0 || fd >= MAX_FD))
		return (-1);
	if (temp_line)
		if (shell_get_line(&temp_line, line))
			return (1);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if ((status = shell_read_fd(fd, line, &temp_line, buf)) == -1)
		return (-1);
	free(buf);
	// if (temp_line == NULL)
	// {
	// 	*line = ft_strdup("");
	// 	return (0);
	// }
	if (status)
		return (1);
	*line = temp_line;
	temp_line = NULL;
	return (0);
}

int				read_line_from_stdin(char **line)
{
	// int			ret;

	// ret = 0;
	if (shell_gnl(0, line) == -1)
	{
		write(1, "get_next_line() error\n", 22);		// add get_next_line error
		return (-1);
		// newline = 1;
	}
	// else if (ret == 1)
	// 	newline = 1;
	// else if (ret == 0)
	// {
	// 	if (sigint_flag)
	// 		newline = 1;
	// 	if (**line != '\0')
	// 	{
	// 		if (shell->last_command)
	// 			free(shell->last_command);
	// 		shell->last_command = ft_strdup(*line);
	// 		newline = 0;
	// 	}
	// 	else if (**line == '\0' && newline)
	// 	{
	// 		if (!TEST)
	// 			ft_printf("exit\n");
	// 		exit(EXIT_SUCCESS);
	// 	}
	// }
	// return (newline);
	return (0);
}
