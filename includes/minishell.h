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
** Parse
*/

void	parse_line(char *str, t_data *data);
int		check_syntax(char **str);
void	error_syntax(char ***str);
char	**expansion(char **str, t_env *envplist);

/*
** Envp
*/

char	**copy_envp(char **envp);
void	set_variable(char ***envp, char *variable);

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

#endif
