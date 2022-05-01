/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils3.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa&hman@student.codam.nl>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 14:53:48 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 16:10:43 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Function creates a new string without the $variable_name
** size of the new str is (ft_strlen(str) - size of the name - $)
** copies first the bit before $ and then the bit after the value name
*/

static char	*create_string_home(char *str, char *temp, t_loc *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < node->start)
	{
		temp[i] = (str[i]);
		i++;
	}
	while (i < node->step1)
	{
		temp[i] = node->val[j];
		i++;
		j++;
	}
	j = 0;
	while (str[node->step2 + j] != '\0')
	{
		temp[i + j] = str[node->start + 1 + j];
		j++;
	}
	return (temp);
}

int	home_value(char **str, int loc, char **envplist)
{
	char	*temp;
	t_loc	*node;

	node = malloc(sizeof(t_loc) * 1);
	if (!node)
		exit_on_error("Error :", 1);
	node->start = loc;
	node->val = get_value_from_envp("HOME", envplist);
	node->val_lenght = ft_strlen(node->val);
	node->step1 = loc + node->val_lenght;
	node->step2 = node->start + 1;
	temp = malloc_string((ft_strlen(*str) - 1) + node->val_lenght);
	temp = create_string_home(*str, temp, node);
	free(*str);
	*str = ft_strdup(temp);
	free(temp);
	loc = node->step1;
	free(node->val);
	free(node);
	return (loc);
}
