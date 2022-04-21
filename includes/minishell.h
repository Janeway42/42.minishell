#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h> 
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <termios.h>
# include <signal.h>
# include <sys/wait.h>
# include "libft.h"

# define PROMPT "minishell> "

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}		t_bool;

/*
** Data structs for minishell
** -------------------------------------------------
** t_list:
** 		index_cmd: counter for the number of cmd blocks
** 		**cmd: double aray storring the commands
** 		*redirect:	a t_red linked list for the redirections
**				->op: the operand
**				->file: the file name
** t_data:
** 		last_exit_code
** 		**envplist: a copy of **envp
** 		term_with_echo: terminal with echtl active
** 		term_without_echo: terminal with echtl deactivated
*/

typedef struct s_red
{
	char				*op;
	char				*file;
	struct s_red		*next;
}						t_red;

typedef struct s_list
{
	int				index_cmd;
	char			**cmd;
	t_red			*redirect;
	struct s_list	*next;
}					t_list;

typedef struct s_data
{
	int				*heredoc_index_array;
	int				last_exit_code;
	char			**envplist;
	int				inpipe_fd;
	int				outpipe_fds[2];
	int				old_stdin;
	int				old_stdout;
	struct termios	term_with_echo;
	struct termios	term_without_echo;
}					t_data;

/*
** Envp
** -------------------------------------------------
*/

char	**copy_envp(char **envp);
void	set_variable(char ***envp, char *variable);
char	**ft_split_variable(char *variable);
int		find_variable_position(char **envp, char *variable);
int		is_valid_env_name(char *name);
char	*get_var_value(char **envp, char *variable);
int		count_variables(char **array);
void	delete_variable(char ***envp, char *variable);

/*
** Parsing
** -------------------------------------------------
*/

t_list	*parse_line(char *str, t_data *data);
int		check_syntax(char **str);

/*
** Expansion
** -------------------------------------------------
*/

char	**expansion(char **str, t_data *data);
int		dollar_sign(char *str);
char	*replace_dollar(char *str, char **envplist);
char	*insert_variable_value(char *str, char *value, int loc, int size_name);

/*
** Command blocks
** -------------------------------------------------
*/

t_list	*set_cmd_blocks(char **tokens);
t_list	*ft_last_block(t_list *x);
int		size_double_array(char **str);
void	join_arrays(char ***cmd, char *token);

/*
** Process command blocks
** -------------------------------------------------
*/

char	*validate_and_locate_cmd(char *cmd, char **envp);
void	process_commands(t_list *cmd_blocks, t_data *data);
int		count_commands(t_list *cmd_blocks);
void	process_redir(t_red *red_list, t_data *data, int cmdnbr);
void	wait_for_child_processes(pid_t last_pid, int amount_commands,
			t_data *data);

/*
**	Heredoc 
** -------------------------------------------------
*/

int		process_heredoc(t_list *cmd_block);
char	*create_temp_file_name(int i);
void	clean_heredoc_temp_files(void);
char	**get_heredoc_delim(t_list *cmd_block);
int		*create_heredoc_index_array(t_list *cmd_block);

/*
** Utils
** -------------------------------------------------
*/

char	**ft_split_minishell(char *str, char c);
int		check_operator(char c);
int		count_strings(char *str, char c);

/*
** Builtin Functions
** -------------------------------------------------
*/

int		ft_unset(char **args, char ***envp_list);
int		ft_env(char **envp_list);
int		ft_cd(char **args, char ***envp_list);
int		ft_exit(char **args, int last_exit_code);
int		ft_pwd(char **envp_list);
int		ft_echo(char **args);
int		ft_export(char **args, char ***envp_list);

/*
** Builtin Utils
** -------------------------------------------------
*/

int		is_it_builtin(char *cmd);
int		execute_builtin(char ***envp_list, char **args, int last_exit_code);
int		is_valid_env_name(char *name);

/*
** Free
** -------------------------------------------------
*/

void	free_double(char ***str);
void	free_string_array(char **array);
void	free_cmd_blocks(t_list **cmd_blocks);
void	free_data(t_data **data);

/*
** Error
** -------------------------------------------------
*/

void	malloc_error_exit(void);
void	exit_on_error(char *message, int exit_code);
void	error_syntax(char ***tokens);

/*
** REMOVE !!!!!!!!!
*/

void	print_envp(char **envp);
void	print_token(char **tokens);
void	print_cmd_blocks(t_list *cmd_blocks);

#endif
