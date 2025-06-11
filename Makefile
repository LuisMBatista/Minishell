# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumiguel <lumiguel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 12:32:03 by treis-ro          #+#    #+#              #
#    Updated: 2025/06/10 11:54:40 by lumiguel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
OBJ_DIR = obj

SRC = \
  $(SRC_DIR)/builtins/builtins.c \
  $(SRC_DIR)/builtins/env_functions.c \
  $(SRC_DIR)/builtins/export.c \
  $(SRC_DIR)/builtins/env.c \
  $(SRC_DIR)/builtins/exit.c \
  $(SRC_DIR)/builtins/test_command_token.c \
  $(SRC_DIR)/command/command.c \
  $(SRC_DIR)/command/command_utils.c \
  $(SRC_DIR)/command/get_input.c \
  $(SRC_DIR)/command/heredoc_utils.c \
  $(SRC_DIR)/command/command_env.c \
  $(SRC_DIR)/command/find_value.c \
  $(SRC_DIR)/command/heredoc.c \
  $(SRC_DIR)/command/redir.c \
  $(SRC_DIR)/env/env_utils.c \
  $(SRC_DIR)/env/shell_env.c \
  $(SRC_DIR)/execution/env_entry.c \
  $(SRC_DIR)/execution/exec_utils.c \
  $(SRC_DIR)/execution/execution.c \
  $(SRC_DIR)/execution/ft_execve.c \
  $(SRC_DIR)/execution/start_exec.c \
  $(SRC_DIR)/execution/child_handler.c \
  $(SRC_DIR)/parsing/parsing.c \
  $(SRC_DIR)/parsing/parsing_util3.c \
  $(SRC_DIR)/parsing/split_token.c \
  $(SRC_DIR)/parsing/parsing_util2.c \
  $(SRC_DIR)/parsing/parsing_utils.c \
  $(SRC_DIR)/signal/signal.c \
  $(SRC_DIR)/free_utils.c \
  $(SRC_DIR)/minishell.c \
  $(SRC_DIR)/utils.c \
  $(SRC_DIR)/free_mutils.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDES = -I includes

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJ)
	make fclean -C libft

fclean: clean
	rm -f $(NAME)

re: fclean all

readline.supp:
	@wget https://raw.githubusercontent.com/benjaminbrassart/minishell/master/readline.supp

valgrind: $(NAME) readline.supp
	@/usr/bin/valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME) $(VALGRIND)
valgrind_i: $(NAME) readline.supp
	@/usr/bin/valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp env -i ./$(NAME) $(VALGRIND)

.PHONY: all clean fclean re
