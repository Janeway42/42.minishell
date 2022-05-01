/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:53:36 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 17:53:37 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**free_array_ft_split(char **array, int position)
{
	int	i;

	i = 0;
	while (i < position)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

void	free_string_array(char **str)
{
	char	**temp;

	temp = str;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(str);
}

void	free_cmd_blocks(t_list **cmd_blocks)
{
	t_list	*temp;
	t_red	*temp_red;

	while (*cmd_blocks != NULL)
	{
		if ((*cmd_blocks)->cmd != NULL)
			free_string_array((*cmd_blocks)->cmd);
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
	free((*data)->heredoc_index_array);
	free(*data);
}
