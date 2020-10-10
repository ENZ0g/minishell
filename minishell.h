/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:04:29 by rhullen           #+#    #+#             */
/*   Updated: 2020/10/10 10:56:46 by jnannie          ###   ########.fr       */
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

# define PATHINPROMPT 0

typedef struct			s_token
{
	char				*data;
	struct s_token		*next;
}						t_token;

typedef struct			s_command
{
	char				**argv;
	struct s_command	*next;
}						t_command;

typedef struct			s_pipe
{
	char				*correct_path;
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
	char				**path;
	t_pipe				*pipe;
	char				*cwd;
	char				**env;
	int					env_len;
	int					last_exit_status;
}						t_shell;

char					*get_from_env(char *to_find, char **env);
void					get_shell_path(t_shell *shell, char **env);
void					get_shell_cwd(t_shell *shell);
void					init_shell(t_shell *shell, char **env);

void					command_add_back(t_command *comands, t_command *new);
t_command				*get_last_command(t_command *comands);
t_command				*new_command(void);
int						get_array_len(char **array);

void					cd(t_shell *shell);
void					close_shell(t_shell *shell);
void					echo(char **args);
void					unset(t_shell *shell);
void					export(t_shell *shell);
void					print_env(t_shell *shell);

void					remove_env(t_shell *shell, char *variable);
void					add_env(t_shell *shell, char *variable, char *value);
void					upd_env(t_shell *shell, char *variable, char *new_value);
int						check_env_exist(t_shell *shell, char *variable);

char					*get_var_name(char *str);
char					*get_var_value(char *str);

// parse.c

t_token					*parse_line(char *line);
t_pipe					*parse_tokens(t_shell *shell, t_token *token);
void					*free_tokens(t_token *token_start);
void					free_pipes(t_shell *shell);

// readline.c

int						read_line_from_stdin(char **line, int newline);
void					print_tokens(t_token *tokens); //dev
void					print_pipes(t_shell *shell); //dev
void					print_prompt(void);

// signals.c

void					set_signals_handlers(void);
void					int_handler(int signum);
void					quit_handler(int signum);

// execute.c

void					execute(t_shell *shell);

#endif
