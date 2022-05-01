/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa&hman@student.codam.nl>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 14:53:48 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 16:37:12 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*null_value(int name_size, int location, char *str)
{
	int		i;
	int		size;
	char	*temp;

	i = 0;
	size = ft_strlen(str) - (name_size + 1);
	temp = malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (NULL);
	temp[size] = '\0';
	while (i < location)
	{
		temp[i] = str[i];
		i++;
	}
	while (str[i + name_size + 1] != '\0')
	{
		temp[i] = str[i + name_size + 1];
		i++;
	}
	return (temp);
}

/*
**-------------------------------------------------------------------------
** Function creates a new string that replaces the $variable_name
** with the variable value from environment
** new str size = (ft_strlen(str) - (name size + $) + value)
** copies first the bit before $, then the value,
** and last what is left after the value name
*/

static char	*create_string(char *str, char *temp, t_loc *node)
{
	int	i;
	int	j;

	i = 0;
	while (i < node->start)
	{
		temp[i] = str[i];
		i++;
	}
	j = 0;
	while (i < (node->step1))
	{
		temp[i] = node->val[j];
		i++;
		j++;
	}
	j = 0;
	while (str[node->step2 + j] != '\0')
	{
		temp[i + j] = str[node->step2 + j];
		j++;
	}
	return (temp);
}

static char	*non_null_value(int name_size, int location, char *str, char *value)
{
	int		size;
	char	*temp;
	t_loc	*node;

	node = malloc(sizeof(t_loc) * 1);
	if (!node)
		exit_on_error("Error :", 1);
	node->start = location;
	node->val = value;
	node->val_lenght = ft_strlen(node->val);
	node->step1 = node->start + node->val_lenght;
	node->step2 = node->start + (name_size + 1);
	size = ft_strlen(str) - (name_size + 1) + node->val_lenght;
	temp = malloc_string(size);
	temp = create_string(str, temp, node);
	free(node);
	return (temp);
}

/*
** Function takes the string that contains $ and replaces
** the variable name with the value of the variable
** double quotation (ascii 34) allows for the presence of variables
** single quotation (ascii 39) transforms all in char
*/

char	*insert_variable_value(char *str, char *value, int loc, int size_name)
{
	int		lenght_val;
	char	*temp;

	lenght_val = ft_strlen(value);
	if (lenght_val == 0)
	{
		if (ft_isdigit((int)str[loc + 1]) == 1)
			size_name = 1;
		temp = null_value(size_name, loc, str);
	}
	else
		temp = non_null_value(size_name, loc, str, value);
	free(str);
	str = ft_strdup(temp);
	free(temp);
	return (str);
}
