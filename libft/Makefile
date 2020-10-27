# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhullen <rhullen@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/23 19:32:49 by rhullen           #+#    #+#              #
#    Updated: 2020/10/26 12:18:30 by rhullen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

GREEN = \033[0;32m
RESET = \033[0;0m

CC = clang
FLAGS = -Werror -Wall -Wextra -g

SRC_DIR = 	./src/
SRC = 		ft_printf.c\
	  		flags.c\
	  		ft_printf_utils.c\
	  		printf_c.c\
	 		printf_di.c\
	 		printf_p.c\
	 		printf_s.c\
	 		printf_u.c\
	 		printf_x.c\
	 		parse_flags.c\
			get_next_line.c\
			get_next_line_utils.c\
			ft_atoi.c\
			ft_bzero.c\
			ft_calloc.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_isprint.c\
			ft_itoa.c\
			ft_memccpy.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_memset.c\
			ft_putchar_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_putstr_fd.c\
			ft_split.c\
			ft_strchr.c\
			ft_strdup.c\
			ft_strjoin.c\
			ft_strlcat.c\
			ft_strlcpy.c\
			ft_strlen.c\
			ft_strmapi.c\
			ft_strncmp.c\
			ft_strcmp.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_strtrim.c\
			ft_substr.c\
			ft_endwith.c\
			ft_tolower.c\
			ft_toupper.c\
			ft_utoa.c\
			ft_putstr_free.c\
			ft_putstrn.c\
			ft_tohex.c\
			ft_lstnew.c\
			ft_lstlast.c\
			ft_lstmap.c\
			ft_lstadd_back.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstadd_front.c\
			ft_lstsize.c\
			ft_arraylen.c\
			ft_strisnum.c\
			ft_printf_error.c\
			ft_isspace.c
SRC_FILES = $(addprefix $(SRC_DIR), $(SRC))

OBJ = $(SRC:.c=.o)
OBJ_DIR = ./objects/
OBJ_FILES = $(addprefix $(OBJ_DIR), $(OBJ))

HEADER = libft.h

all: $(NAME)

$(NAME): $(HEADER) $(SRC_FILES) $(OBJ_FILES)
	ar rc $(NAME) $(OBJ_FILES)
	ranlib $(NAME)
	@echo "$(GREEN) $(NAME) created $(RESET)"

clean:
	rm -rf $(OBJ_DIR)
	@echo "$(GREEN) Objectfiles deleted $(RESET)"

fclean: clean
	rm -f $(NAME)
	@echo "$(GREEN) $(NAME) deleted $(RESET)"

re: fclean $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	$(CC) $(FLAGS) -c $^ -o $@ -I.
