/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_cmd_blocks_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:52:28 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 17:52:46 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

void	join_arrays(char ***cmd, char *token)
{
	int		i;
	int		size;
	char	**new_block;

	i = 0;
	size = count_arrays(*cmd) + 1;
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
