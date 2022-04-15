#include "../includes/minishell.h"

t_list	*ft_last_block(t_list *x)
{
	t_list	*last;

	if (!x)
		return (NULL);
	last = x;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

int	size_double_array(char **str) // duplicate? 
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

void	join_arrays(char ***cmd, char *token) // duplicate function insert_variable(char ***envp, char *variable)
{
	int		i;
	int		size;
	char	**new_block;

	i = 0;
	size = size_double_array(*cmd) + 1;
	new_block = malloc(sizeof(char *) * (size + 1));
	if (!new_block)
		malloc_error_exit();
	new_block[size] = NULL;
	while (i < (size - 1))
	{
		new_block[i] = ft_strdup((*cmd)[i]);
		if (!new_block[i])
			malloc_error_exit();
		i++;
	}
	new_block[size - 1] = ft_strdup(token);
	if (!new_block[size - 1])
		malloc_error_exit();
	free_string_array(*cmd);
	*cmd = new_block;
}
