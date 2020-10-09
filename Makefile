NAME = minishell
FLAGS = -Wall -Werror -Wextra
CC = gcc
SRC = main.c

PIPE_SRC =	pipe_test.c\
			pipe_test_utils.c\
			t_comands.c\
			cd.c\
			echo.c\
			env.c\
			exit.c\
			export.c\
			split_env_variable.c\
			standart_functions_utils.c\
			unset.c

.PHONY: all fclean

all: $(NAME)

./libft/libft.a:
	make -C ./libft

$(NAME): main.c ./libft/libft.a
	$(CC) $(FLAGS) $(SRC) -o $(NAME) -L./libft -I./libft -lft

pipe: $(PIPE_SRC) minishell.h
	$(CC) $(PIPE_SRC) -o pipe -L./libft -I. -I./libft -lft

fclean:
	rm -f minishell
	rm -f pipe
	make fclean -C ./libft