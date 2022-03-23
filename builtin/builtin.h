#ifndef BUILTIN_H
# define BUILTIN_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../lib/libft/libft.h"

//struct for redirections
typedef struct s_redir
{
	char			*operator;
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

//function of ft_strcmp.c
int		ft_strcmp(const char *s1, const char *s2);

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

//functions in errors.c
void	malloc_error_exit(void);

#endif

/*
//function of envp_list_utils_linked.c
void	insert_back_of_list(t_env **begin_list, t_env *node);
void	insert_node_sorted(t_env **begin_list, t_env *node);
void	set_env(t_env **envp_list, char *key, char *value);
void	del_env(t_env **envp_list, char *key);
char	*get_env(t_env *envp_list, char *key);

//functions in  envp_copy_linked.c
t_env	*create_node(char *key, char *value);
char	**ft_split_env(char *env);
void	free_envp_list(t_env *list);
t_env	*envp_copy(char **envp);
*/
