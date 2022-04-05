#include "../includes/minishell.h"

void	free_double(char ***str)
{
	char	**temp;

	temp = *str;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(*str);
}

void	error_syntax(char ***tokens)
{
	printf("error syntax\n");
	free_double(tokens);
}

void	malloc_error_exit(void)  // duplicate function 
{
	printf("Malloc error.\n");
	exit(1);
}

void	free_string_array(char **array)  // duplicate function 
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_cmd_blocks(t_list **cmd_blocks)
{
	t_list	*temp;
	t_red	*temp_red;

	temp = *cmd_blocks;
	while (*cmd_blocks != NULL)
	{
		while ((*cmd_blocks)->redirect != NULL)
		{
			temp_red = temp->redirect;
			free(temp_red);
			temp->redirect = temp->redirect->next;
		}
		temp = *cmd_blocks;
		*cmd_blocks = (*cmd_blocks)->next;
		free(temp);
	}
}

void	free_data(t_data **data)
{
	free_string_array((*data)->envplist);
	free(*data);
}