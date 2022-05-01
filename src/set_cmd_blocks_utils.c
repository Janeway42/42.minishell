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

// int	size_double_array(char **str) // duplicate envp_copy.c 
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != NULL)
// 		i++;
// 	return (i);
// }

void	join_arrays(char ***cmd, char *token)
{
	int		i;
	int		size;
	char	**new_block;

	i = 0;
	size = count_arrays(*cmd) + 1;   //size_double_array(*cmd) + 1;
	new_block = malloc(sizeof(char *) * (size + 1));
	if (!new_block)
		exit_on_error("Error :", 1);
	new_block[size] = NULL;
	while (i < (size - 1))
	{
		new_block[i] = ft_strdup((*cmd)[i]);
		if (!new_block[i])
			exit_on_error("Error :", 1);
		i++;
	}
	new_block[size - 1] = ft_strdup(token);
	if (!new_block[size - 1])
		exit_on_error("Error :", 1);
	free_string_array(*cmd);
	*cmd = new_block;
}
