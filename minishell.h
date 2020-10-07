/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:04:29 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/07 12:15:13 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include "libft.h"

typedef struct			s_comands
{
	char				*correct_path;
	char				**args;
	short				is_out_in_file;
	short				is_append;
	char				*out_file_name;
	short				is_input_from_file;
	char				*input_file_name;
	short				is_pipe;
	struct s_comands	*next;
}						t_comands;

typedef struct			s_shell
{
	char				**path;
	t_comands			*comands;
	char				*cwd;
	short				counter;
}						t_shell;

char					*get_from_env(char *to_find, char **env);
void					get_shell_path(t_shell *shell, char **env);
void					get_shell_cwd(t_shell *shell, char **env);
void					init_shell(t_shell *shell, char **env);

#endif