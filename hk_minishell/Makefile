# compiler configuration
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
UNAME = $(shell uname -s)

# Project info
NAME = minishell

# source code
SRC_DIR = src
SRC_FILES = $(addprefix $(SRC_DIR)/,\
	minishell.c \
	errors.c \
	envp_copy.c \
	envp_utils.c \
	builtin.c \
	builtin_env_cd_unset.c \
	builtin_export.c \
	builtin_exit_pwd_echo.c \
	ft_strcmp.c \
	validation_cmd.c \
	process_cmds.c \
	redirections.c)

# include directory
INCLUDES_FLAG = -Iincludes

# object code
OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#Library libft
LIBFT_DIR = lib/libft
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# Newer readline library
ifeq ($(UNAME), Darwin)
	RL_INCLUDE_FLAG = -I$(shell brew --prefix readline)/include 
	RL_LIBRARY_FLAG = -L$(shell brew --prefix readline)/lib -lreadline
endif
ifeq ($(UNAME), Linux)
	RL_INCLUDE_FLAG =
	RL_LIBRARY_FLAG = -lreadline
endif

all: $(NAME)

test: 
	echo $(OBJ_FILES)

$(NAME) : $(OBJ_FILES)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) $(INCLUDES_FLAG) $(LIBFT_FLAGS) $(RL_INCLUDE_FLAG) \
	$(RL_LIBRARY_FLAG)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) $(INCLUDES_FLAG) $(RL_INCLUDE_FLAG) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ_FILES)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

