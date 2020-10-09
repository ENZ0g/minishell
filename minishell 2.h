/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 01:40:03 by jnannie           #+#    #+#             */
/*   Updated: 2020/10/09 16:38:04 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

// # define OP_IN_FILE '>'
// # define OP_FROM_FILE '<'
// # define OP_PIPE '|'
// # define OP_END_OF_PIPE ';'
// # define REGULAR_TEXT 0

typedef struct			s_token
{
	char				*data;
	// char				type;
	struct s_token		*next;
}						t_token;

typedef struct			s_command
{
	char				*executable;
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
	char				**env;
	t_pipe				*pipe;
	char				*cwd;
}						t_shell;

t_shell					*shell;

t_token					*parse_line(char *line);
t_pipe					*parse_tokens(t_token *token);
void					*free_tokens(t_token *token_start);

#endif
