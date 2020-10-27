# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 11:57:45 by rhullen           #+#    #+#              #
#    Updated: 2020/10/26 13:03:12 by rhullen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Werror -Wextra -g
CC = gcc

SRC_DIR = ./shell_srcs/
SRC =	main.c\
		utils_1.c\
		utils_2.c\
		cd.c\
		echo.c\
		env.c\
		exit.c\
		export.c\
		split_env_variable.c\
		standart_functions_utils.c\
		unset.c\
		execute.c\
		parse_line.c\
		readline.c\
		signals.c\
		parse_tokens.c\
		expand_str.c\
		check_tokens.c\
		check_command.c\
		exit_shell.c\
		expand_variable.c\
		execute_utils.c\
		parse_line_utils.c\
		parse_line_utils2.c\
		print_error.c\
		utils_3.c\
		parse_tokens_utils.c\
		expand_str_utils.c\
		readline_utils.c\
		check_command_utils.c
SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))

OBJ = $(SRC:.c=.o)
OBJ_DIR = ./objects/
OBJ_FILES = $(addprefix $(OBJ_DIR), $(OBJ))

all: libft $(NAME)

libft:
	@make -C libft/

$(NAME): $(OBJ_FILES)
	$(CC) $(FLAGS) $(OBJ_FILES) -o $(NAME) -L./libft -lft
	
clean:
	make clean -C libft/
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c minishell.h libft/libft.a
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@ -I./libft -I.

.PHONY: all re clean fclean libft