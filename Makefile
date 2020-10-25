NAME = minishell
FLAGS = -Wall -Werror -Wextra -g
CC = gcc
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
		dev.c\
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
		utils3.c\
		parse_tokens_utils.c\
		expand_str_utils.c\
		readline_utils.c\
		check_command_utils.c

all: makelibft $(NAME)

makelibft:
	@make -C libft/

$(NAME): $(SRC) minishell.h ./libft/libft.a
	$(CC) $(FLAGS) $(SRC) -o $(NAME) -L./libft -I./libft -lft

re: fclean all

clean:
	rm -f libft/objects/*.o
	rm -f *.o

fclean: clean
	rm -f libft/libft.a
	rm -f minishell
	make fclean -C ./libft

.PHONY: all re clean fclean makelibft