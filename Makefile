NAME = minishell
CFLAGS	= -Wall -Werror -Wextra -g #-fsanitize=address
UNAME = $(shell uname)

S_SRC	=	main.c\
			main_utils.c\
			parse.c\
			check_syntax.c\
			expansion.c\
			expansion_utils1.c\
			expansion_utils2.c\
			expansion_utils3.c\
			set_cmd_blocks.c\
			set_cmd_blocks_utils.c\
			process_commands.c\
			process_commands_utils.c\
			process_commands_validation.c\
			redirections.c\
			process_heredoc.c\
			process_heredoc_utils.c\
			signals.c
S_PATH	=	src/
S_OBJ	=	$(S_SRC:%.c=$(S_PATH)%.o)

BUILT_SRC	=	builtin_start_echo.c\
				builtin_cd.c\
				builtin_env_unset.c\
				builtin_exit_pwd.c\
				builtin_export.c
BUILT_PATH	=	builtins/
BUILT_OBJ	=	$(BUILT_SRC:%.c=$(BUILT_PATH)%.o)

UTILS		=	ft_split_minishell.c\
				ft_split_minishell_utils.c\
				error.c\
				free.c\
				malloc.c
			
UTILS_PATH	=	utils/
UTILS_OBJ	=	$(UTILS:%.c=$(UTILS_PATH)%.o)

ENV			=	envp_copy.c\
				envp_utils.c
ENV_PATH	=	envp/
ENV_OBJ		=	$(ENV:%.c=$(ENV_PATH)%.o)

OBJ_FILES = $(S_OBJ) $(BUILT_OBJ) $(UTILS_OBJ) $(ENV_OBJ)

ifeq ($(UNAME), Linux)
	RL_FLAGS = -lreadline
else
	RL_FLAGS = -L$(shell brew --prefix readline)/lib -lreadline
	RL_INCLUDE_FLAGS = -I$(shell brew --prefix readline)/include
endif
INCLUDES_FLAG = -Iincludes

all: $(NAME)

$(NAME): $(OBJ_FILES)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ_FILES) $(RL_FLAGS) $(RL_INCLUDE_FLAGS) $(INCLUDES_FLAG) libft/libft.a -o $(NAME)
	
%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) $(RL_INCLUDE_FLAGS) $(INCLUDES_FLAG) -c $< -o $@ 

clean:
	make clean -C libft
	$(RM) $(OBJ_FILES)

fclean: clean
	$(RM) libft/libft.a
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re