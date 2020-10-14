/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:04:29 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/14 20:35:54 by rhullen          ###   ########.fr       */
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

extern int				sigint_flag;

typedef struct			s_token // temporary for parsing
{
	char				*data;
	struct s_token		*next;
}						t_token;

typedef struct			s_command
{
	int					is_found;
	char				*correct_path; // need to be freed
	char				**argv;
	short				is_out_in_file;
	short				is_append;
	char				*out_file_name;
	short				is_input_from_file;
	char				*input_file_name;
	short				is_pipe;
	struct s_command	*next;
}						t_command;

typedef struct			s_pipe
{
	int					is_found;
	char				*correct_path; // need to be freed
	char				**argv;
	short				is_out_in_file;
	short				is_append;
	char				*out_file_name;
	short				is_input_from_file;
	char				*input_file_name;
	short				is_pipe;

	t_command			*command;
	struct s_pipe		*next;
}						t_pipe;

typedef struct			s_shell
{
	char				**path; // init
	t_pipe				*pipe; // init 0
	t_command			*command;
	char				*cwd; // init // need to be freed
	char				**env; // init // need to be freed
	int					env_len; // init
	int					last_exit_status; // inti 0
	char				*last_command; // need to be freed
	char				**buildin_commands;
	int					fd_in;
	int					fd_out;
}						t_shell;

/*
** utils_1.c
*/

char					*get_from_env(char *to_find, char **env);
void					get_env(t_shell *shell, char **env);
void					get_buildin_commands(t_shell *shell);
void					init_shell(t_shell *shell, char **env);

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

/*
** cd.c
*/

void					cd(t_shell *shell, char **args);

/*
** exit.c
*/

void					close_shell(t_shell *shell);

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
int						parse_tokens(t_shell *shell, t_token *token);
void					*free_tokens(t_token *token_start);
void					free_pipes(t_shell *shell);
int						is_buildin_command(t_shell *shell, char *command);

/*
** readline.c
*/

int						read_line_from_stdin(t_shell *shell, char **line, int newline);
void					print_prompt(void);

/*
** signals.c
*/

void					set_signals_handlers(void);
void					int_handler(int signum);
void					quit_handler(int signum);

/*
** execute.c
*/

void					execute(t_shell *shell);

/*
** dev.c
*/

void					print_tokens(t_token *tokens);
void					print_commands(t_shell *shell);
void					print_argv(char **argv);

#endif
