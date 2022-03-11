#ifndef MINISHEL_H
# define MINISHEL_H

# include <unistd.h> 
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "libft.h"
# include "builtin.h"

# define PROMPT "minishell: "

typedef struct	s_arg
{
	struct s_arg		*next;
	char				*arg;
}				t_arg;

typedef struct			s_red
{
	struct s_red		*next;
	char				*op;
	char				*word;
}						t_red;

typedef struct	s_list
{
	struct s_list	*next;
	t_red			*redirect;
	char			*cmd;
	t_arg			*arguments;
}				t_list;

void parse_line(char *str, t_env *envplist);
char **expansion(char **str, t_env	*envplist);

void	free_double(char ***str);

/*
// Check Syntax
*/

int	check_syntax(char **str);
void	error_syntax(char ***str);
char **ft_split_minishell(char *str, char c);

char **expansion(char **str, t_env	*envplist);


#endif
