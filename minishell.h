/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:04:29 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/24 15:21:06 by jnannie          ###   ########.fr       */
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

extern int				g_sigint_flag;
extern int				g_last_pid;
extern int				g_last_exit_status;
extern int				g_child_pid_count;

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
	short				is_append;
	char				*out_file_name;
	char				*input_file_name;
	short				is_pipe;
	int					file_fd_in;
	int					file_fd_out;
}						t_command;

typedef struct			s_shell
{
	char				**path;
	t_command			*command;
	char				*cwd;
	char				**env;
	int					env_len;
	char				**buildin_commands;
	int					fd_stdin;
	int					fd_stdout;
	int					fd_pipe[2];
	int					parsing_error;
	char				*last_var;
	t_token				*tokens;
	char				*line;
}						t_shell;

typedef struct			s_quotes
{
	int					sq;
	int					dq;
}						t_quotes;

/*
** utils_1.c
*/
char					*get_from_env(char *to_find, char **env);
void					get_env(t_shell *shell, char **env);
void					get_buildin_commands(t_shell *shell);
t_shell					*init_shell(char **env);
void					print_prompt(void);

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
void					upd_env(t_shell *shell, char *variable,
								char *new_value);
int						check_env_exist(t_shell *shell, char *variable);

/*
** split_env_variable.c
*/
char					*get_var_name(t_shell *shell, char *str);
char					*get_var_value(t_shell *shell, char *str);

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
void					free_tokens(t_shell *shell);
int						is_buildin_command(t_shell *shell, char *command);
char					*skip_whitespaces(char *str);
void					print_error(char *error_source, char *error_msg,
									int new_line);

/*
** readline.c
*/
int						read_line_from_stdin(t_shell *shell, char **line);

/*
** signals.c
*/
void					set_signals_handlers(void);

/*
** execute.c
*/
void					execute(t_shell *shell, t_command *command);
int						wait_for_process(void);
void					run_buildin(t_shell *shell, t_command *command);

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
void					check_correct_command(t_shell *shell,
								t_command *command, char *data);

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
int						expand_variable(t_shell *shell, char **new_data,
									char **data);

/*
** errors.c
*/

void					print_error(char *error_source, char *error_msg,
									int new_line);

/*
** fork_utils.c
*/

int						wait_for_process(void);
int						set_fd_in(t_shell *shell, t_command *command);
int						set_fd_out(t_shell *shell, t_command *command);
void					child_process(t_shell *shell, t_command *command);
void					parent_process(t_shell *shell, int pid);

/*
** parse_line_utils.c
*/

char					*skip_whitespaces(char *str);
int						skip_backslashed(t_token *token, char **line, int i);
t_token					*token_init(t_shell *shell, size_t len);
t_token					*create_next_token(t_shell *shell, t_token *token,
											char *line);

/*
** parse_line_utils2.c
*/

int						process_single_quote(t_quotes *quote, t_token *token,
											char **line, int i);
int						process_double_quote(t_quotes *quote, t_token *token,
											char **line, int i);
int						process_operators(t_shell *shell, t_token **token,
											char **line, int i);
int						process_whitespaces(t_shell *shell, t_token **token,
											char **line, int i);
int						process_out_operator(t_shell *shell, t_token **token,
											char **line, int i);

/*
** parse_line_utils2.c
*/
int						check_quotes_error(int single_q, int double_q,
								t_shell *shell, t_token *token);

/*
** parse_line_utils2.c
*/
void					ambiguous_redirect_error(t_shell *shell);
void					open_file_error(t_shell *shell, char *filename);
t_token					*get_next_token(t_token *token);

#endif
