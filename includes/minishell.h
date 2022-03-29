#ifndef MINISHEL_H
# define MINISHEL_H

# include <unistd.h> 
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <termios.h>
# include "libft.h"
# include "builtin.h"

# define PROMPT "minishell: "

typedef struct			s_red
{
	struct s_red		*next;
	char				*op;
	char				*file;
}						t_red;

typedef struct		s_list
{
	struct s_list	*next;
	t_red			*redirect;
	char			**cmd;
	int				index_cmd;
}					t_list;

typedef struct		s_data
{
	char			**envplist;
	struct termios	old_term;
	struct termios	new_term;
	int				last_exit_code;
}					t_data;

/*
** Envp
*/

char	**copy_envp(char **envp);
void	set_variable(char ***envp, char *variable);
char	**ft_split_variable(char *variable);
int		find_variable_position(char **envp, char *variable);
char	*get_var_value(char **envp, char *variable);
int		count_variables(char **array);
void	delete_variable(char ***envp, char *variable);

/*
** Parse
*/

void	parse_line(char *str, t_data *data);
int		check_syntax(char **str);
void	error_syntax(char ***str);
char	**expansion(char **str, t_data *data);
t_list	*set_cmd_blocks(char **tokens);

/*
** Expansion
*/

char	**expansion(char **str, t_data *data);
char	*insert_variable_value(char *str, char *value, int loc, int size_name);
char	*non_null_value(int name_size, int location, char *str, char *value);
char	*null_value(int name_size, int location, char *str);
int		validity_name(char c, int location);
char	*remove_quotes(char *str);

/*
** Utils
*/

char **ft_split_minishell(char *str, char c);

/*
** Error / Free
*/

void	free_double(char ***str);
void	malloc_error_exit(void);
void	free_string_array(char **array);

/*
** REMOVE !!!!!!!!!
*/

void print_token(char **tokens);
void print_cmd_blocks(t_list *cmd_blocks);

#endif
