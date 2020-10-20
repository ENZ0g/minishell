/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:04:29 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/20 21:34:18 by rhullen          ###   ########.fr       */
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
# include <sys/syslimits.h>
# include <sys/stat.h>

# define PATHINPROMPT 1
# define SHELL_PROMPT "minishell$ "
# define TEST 1

typedef struct			s_token
{
	char				*data;
	struct s_token		*next;
}						t_token;

typedef struct			s_command
{
	int					is_found;
	char				*correct_path;
	char				**argv;
	short				is_out_in_file;
	short				is_append;
	char				*out_file_name;
	short				is_input_from_file;
	char				*input_file_name;
	short				is_pipe;
	int					file_fd_in;
	int					file_fd_out;
	struct s_command	*next;
}						t_command;

typedef struct			s_shell
{
	char				**path;
	t_command			*command;
	char				*cwd;
	char				**env;
	int					env_len;
	int					last_exit_status;
	char				*last_command;
	char				**buildin_commands;
	int					fd_stdin;
	int					fd_stdout;
	int					fd_pipe[2];
	int					parsing_error;
	char				*last_var;
	int					sigint_flag;
	int					child_pid_count;
	int					pid;
}						t_shell;

extern t_shell			*shell;

/*
** utils_1.c
*/

char					*get_from_env(char *to_find, char **env);
void					get_env(t_shell *shell, char **env);
void					get_buildin_commands(t_shell *shell);
t_shell					*init_shell(char **env);

/*
** utils_2.c
*/

void					get_shell_cwd(t_shell *shell);
char					*get_prompt(t_shell *shell);
int						get_array_len(char **array);
void					get_shell_path(t_shell *shell, char **env);
void					upd_shell_path(t_shell *shell);


/*
** unset.c
*/

void					unset(t_shell *shell, t_command *command);

/*
** t_commands_utils.c
*/

void					command_add_back(t_command *comands, t_command *new);
t_command				*get_last_command(t_command *comands);
t_command				*new_command(void);

/*
** standart_functions_utils.c
*/

void					remove_env(t_shell *shell, char *variable);
void					add_env(t_shell *shell, char *variable, char *value);
void					upd_env(t_shell *shell, char *variable, char *new_value);
int						check_env_exist(t_shell *shell, char *variable);

/*
** split_env_variable.c
*/

char					*get_var_name(char *str);
char					*get_var_value(char *str);
void					fatal_error(void);

/*
** cd.c
*/

void					cd(t_shell *shell, char **args);

/*
** exit.c
*/

void					close_shell(t_shell *shell);
void					total_free(void);
void					nested_free(char **array);

/*
** echo.c
*/

void					echo(t_shell *shell, char **args);

/*
** export.c
*/

void					export(t_shell *shell, t_command *command);

/*
** env.c
*/

void					print_env(t_shell *shell);

/*
** parce.c
*/

t_token					*parse_line(char *line);
t_token					*parse_tokens(t_shell *shell, t_token *token);
void					*free_tokens(t_token *token);
void					free_pipes(t_shell *shell);
int						is_buildin_command(t_shell *shell, char *command);
int						check_tokens(t_shell *shell, t_token *tokens);
char					*skip_whitespaces(char *str);

/*
** readline.c
*/

int						read_line_from_stdin(char **line);
void					print_prompt(void);

/*
** signals.c
*/

void					set_signals_handlers(void);

/*
** execute.c
*/

void					execute(t_shell *shell);
int						wait_for_process(t_shell *shell);

#endif
