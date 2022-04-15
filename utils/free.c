#include "../includes/minishell.h"

void	free_double(char ***str) // duplicate function -> choose one 
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

void	free_string_array(char **array) // duplicate function -> choose one 
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

	while (*cmd_blocks != NULL)
	{
		if ((*cmd_blocks)->cmd != NULL)
			free_double(&(*cmd_blocks)->cmd);
		while ((*cmd_blocks)->redirect != NULL)
		{
			temp_red = (*cmd_blocks)->redirect;
			(*cmd_blocks)->redirect = ((*cmd_blocks)->redirect)->next;
			free(temp_red->op);
			free(temp_red->file);
			free(temp_red);
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
