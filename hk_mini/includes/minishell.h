#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define PROMPT "minishell>"

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}		t_bool;

//----------------------------------------------------------------------------
//	DATASTRUCTS FOR MINISHELL
//----------------------------------------------------------------------------
//struct for redirections
typedef struct s_redir
{
	char			*op;
	char			*argument;
	struct s_redir	*next;
}				t_redir;

//struct for the command block
typedef struct s_cmd_block
{
	int					cmdnbr;
	int					inputfd;
	int					outputfd;
	t_redir				*redirs;
	char				**cmd_args;
	struct s_cmd_block	*next;
}				t_cmd_block;

typedef struct s_data
{
	char			**envp_list;
	int				last_exit_code;
	int				inpipe_fd;
	int				outpipe_fds[2];
	int				old_stdin;
	int				old_stdout;
	struct termios	old_term;
	struct termios	new_term;

}				t_data;

//----------------------------------------------------------------------------
//	ENVP AND ENVP UTILITY FUNCTIONS
//----------------------------------------------------------------------------

//functions of envp_copy.c
void	free_string_array(char **array);
int		count_variables(char **array);
int		find_variable_position(char **envp, char *variable);
char	**copy_envp(char **envp);
char	**ft_split_variable(char *variable);

//functions of envp_utils.c
void	insert_variable(char ***envp, char *variable);
void	set_variable(char ***envp, char *variable);
void	delete_variable(char ***envp, char *variable);
char	*get_var_value(char **envp, char *variable);

//----------------------------------------------------------------------------
//	BUILTIN FUNCTIONS
//----------------------------------------------------------------------------

//functions in builtin.c
int		is_it_builtin(char *cmd);
int		execute_builtin(char ***envp_list, char **args, int last_exit_code);

//functions in builtin_env_cd_unset.c
int		ft_unset(char **args, char ***envp_list);
int		ft_env(char **envp_list);
int		ft_cd(char **args, char ***envp_list);

//functions in builtin_exit_pwd_echo.c
int		ft_exit(char **args, int last_exit_code);
int		ft_pwd(char **envp_list);
int		ft_echo(char **args);

//functions in builtin_export.c
int		is_valid_env_name(char *name);
int		ft_export(char **args, char ***envp_list);

//----------------------------------------------------------------------------
//	VALIDATE COMMANDS
//----------------------------------------------------------------------------

//fuctions of validation.c
char	*validate_and_locate_cmd(char *cmd, char **envp);

//----------------------------------------------------------------------------
//	OTHER FILES
//----------------------------------------------------------------------------
//functions in errors.c
void	exit_on_error(char *message, int exit_code);

//function of ft_strcmp.c
int		ft_strcmp(const char *s1, const char *s2);

#endif
