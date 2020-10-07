NAME = minishell
FLAGS = -Wall -Werror -Wextra
CC = gcc
SRC = main.c

.PHONY: all fclean

all: $(NAME)

$(NAME): main.c
	$(CC) $(FLAGS) $(SRC) -o $(NAME) -L./libft -I./libft -lft

pipe: pipe_test.c pipe_test_utils.c minishell.h
	$(CC) pipe_test.c pipe_test_utils.c -o pipe -L./libft -I. -I./libft -lft

fclean:
	rm -f minishell
	rm -f pipe