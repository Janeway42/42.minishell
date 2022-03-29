NAME = minishell
CFLAGS	= -Wall -Werror -Wextra -g -fsanitize=address

S_SRC	=	main.c\
			parse.c\
			check_syntax.c\
			expansion.c\
			expansion_utils.c\
			set_cmd_blocks.c
S_PATH	=	src/
S_OBJ	=	$(S_SRC:%.c=$(S_PATH)%.o)

UTILS		=	ft_split_minishell.c\
				error_free.c
UTILS_PATH	=	utils/
UTILS_OBJ	=	$(UTILS:%.c=$(UTILS_PATH)%.o)

ENV			=	envp_copy.c\
				envp_utils.c
ENV_PATH	=	envp_copy_c/
ENV_OBJ		=	$(ENV:%.c=$(ENV_PATH)%.o)

OBJ_FILES = $(S_OBJ) $(UTILS_OBJ) $(ENV_OBJ)

RL_FLAGS = -L$(shell brew --prefix readline)/lib -lreadline
RL_INCLUDE_FLAGS = -I$(shell brew --prefix readline)/include

all: $(NAME)

$(NAME): $(OBJ_FILES)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ_FILES) $(RL_FLAGS) $(RL_INCLUDE_FLAGS) libft/libft.a -o $(NAME)
	
%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) $(RL_INCLUDE_FLAGS) -c $< -o $@ 

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