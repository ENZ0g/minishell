/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:04:29 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/23 11:39:02 by jnannie          ###   ########.fr       */
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
# define TEST 0
# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2

extern int				g_sigint_flag;
extern int				g_last_pid;
extern int				g_last_exit_status;
extern int				g_child_pid_count;

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
	// short				is_out_in_file;
	short				is_append;
	char				*out_file_name;
	// short				is_input_from_file;
	char				*input_file_name;
	short				is_pipe;
	int					file_fd_in;
	int					file_fd_out;
	// struct s_command	*next;
}						t_command;

typedef struct			s_shell
{
	char				**path; // init
	t_command			*command;
	char				*cwd; // init // need to be freed
	char				**env; // init // need to be freed
	int					env_len; // init
	// int					last_exit_status; // inti 0
	// char				*last_command; // need to be freed
	char				**buildin_commands;
	int					fd_stdin;
	int					fd_stdout;
	int					fd_pipe[2];
	int					parsing_error;
	char				*last_var;
	// char				*line;			// to del
	// int					sigint_flag;
	// int					fd_in;
	// int					fd_out;
	// int					child_pid_count;
	t_token				*tokens;
	// int					pid;
	char				*line;
}						t_shell;

// extern t_shell			*g_shell;

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

void					echo(char **args);

/*
** export.c
*/

void					export(t_shell *shell, t_command *command);

/*
** env.c
*/

void					print_env(t_shell *shell);

/*
** parce_line.c
*/

t_token					*parse_line(t_shell *shell, char *line);
// t_token					*parse_tokens(t_token *token);
void					free_tokens(t_shell *shell);
// void					free_pipes(t_shell *shell);
int						is_buildin_command(t_shell *shell, char *command);
char					*skip_whitespaces(char *str);
void					print_error(char *error_source, char *error_msg, int new_line);		// to del

/*
** readline.c
*/

int						read_line_from_stdin(t_shell *shell, char **line);
void					print_prompt(void);

/*
** signals.c
*/

void					set_signals_handlers(void);
// void					int_handler(int signum);
// void					quit_handler(int signum);
// void					child_quit_handler(int signum);

/*
** execute.c
*/

void					execute(t_shell *shell, t_command *command);
int						wait_for_process(void);

/*
** dev.c
*/

void					print_tokens(t_token *tokens);
void					print_commands(t_shell *shell);
void					print_argv(char **argv);
void					nested_free(char **array);

/*
** expand_str.c
*/
int						expand_str(t_shell *shell, t_token *token, char *data);

/*
** parse_tokens.c
*/
t_token					*parse_tokens(t_shell *shell, t_token *token);
int						is_escape_char(char ch);

/*
** check_command.c
*/
void					check_correct_command(t_shell *shell, t_command *command, char *data);

/*
** exit_shell.c
*/
void					exit_shell(t_shell *shell, int exit_status);

/*
** main.c
*/
void					free_command(t_shell *shell);

/*
** check_tokens.c
*/
int						check_tokens(t_shell *shell, t_token *tokens);

/*
** expand_variable.c
*/
int						expand_variable(t_shell *shell, char **new_data, char **data);

#endif
