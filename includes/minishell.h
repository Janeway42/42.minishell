#ifndef _MINISHEL_H_
#define _MINISHEL_H_

#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

#define PROMPT "minishell: "

typedef struct s_cmd_block
{
	int		fd_input; 
	int		fd_output;
	char	**cmd;
	char	*arguments;
}				t_cmd_block;

typedef struct s_list
{
	struct	s_list *next;
	struct	s_cmd_block block;
	int					location;
	struct	s_list *prev;
}				t_list;

typedef struct s_data
{
	struct	s_list	*line_arg;
	char			**commands;
}				t_data;

t_list *create_new_elem(int number);
void	add_at_the_end(t_list **line_arg, t_list *element);


#endif
