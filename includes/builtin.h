#ifndef BUILTIN_H
# define BUILTIN_H

#include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

int	ft_strcmp(const char *s1, const char *s2);

//function of envp_list_utils
void	insert_back_of_list(t_env **begin_list, t_env *node);
void	insert_node_sorted(t_env **begin_list, t_env *node);
void	set_env(t_env **envp_list, char *key, char *value);
void	del_env(t_env **envp_list, char *key);
char	*get_env(t_env *envp_list, char *key);

//functions in  envp_copy
t_env	*create_node(char *key, char *value);
char	**ft_split_env(char *env);
void	free_envp_list(t_env *list);
t_env	*envp_copy(char **envp);

#endif