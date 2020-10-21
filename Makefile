NAME = minishell
FLAGS = -Wall -Werror -Wextra -g
CC = gcc
SRC =	main.c\
		utils_1.c\
		utils_2.c\
		t_command_utils.c\
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
		dev.c\
		parse_tokens.c\
		expand_str.c\
		check_tokens.c\
		check_command.c\
		exit_shell.c

.PHONY: all fclean

all: $(NAME)

./libft/libft.a:
	make -C ./libft

$(NAME): $(SRC) minishell.h ./libft/libft.a
	$(CC) $(FLAGS) $(SRC) -o $(NAME) -L./libft -I./libft -lft

fclean:
	rm -f minishell
	make fclean -C ./libft