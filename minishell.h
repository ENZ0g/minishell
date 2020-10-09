/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:04:29 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/09 15:50:13 by rhullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include "libft.h"
# include <fcntl.h>
# include <string.h>

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
	char				**env;
	int					env_len;
	int					last_exit_status;
}						t_shell;

char					*get_from_env(char *to_find, char **env);
void					get_shell_path(t_shell *shell, char **env);
void					get_shell_cwd(t_shell *shell, char **env);
void					init_shell(t_shell *shell, char **env);

void					comand_add_back(t_comands *comands, t_comands *new);
t_comands				*get_last_comand(t_comands *comands);
t_comands				*new_comand(void);
int						get_array_len(char **array);

void					cd(t_shell *shell);
void					close_shell(t_shell *shell);
void					echo(t_shell *shell);
void					unset(t_shell *shell);
void					export(t_shell *shell);
void					print_env(t_shell *shell);

void					remove_env(t_shell *shell, char *variable);
void					add_env(t_shell *shell, char *variable, char *value);
void					upd_env(t_shell *shell, char *variable, char *new_value);
int						check_env_exist(t_shell *shell, char *variable);

char					*get_var_name(char *str);
char					*get_var_value(char *str);

#endif