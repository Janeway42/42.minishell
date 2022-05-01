/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils1.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa&hman@student.codam.nl>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 14:53:48 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 17:39:09 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Bash variable can contain only letters, numbers and underscore
** The first character of the name can not be a diggit
** Function looks at whether those conditions are met
*/

int	validity_name(char c, int location)
{
	int	n;

	n = (int) c;
	if (location == 0 && ft_isdigit(c) == 1)
		return (1);
	if (ft_isdigit(c) == 1 || ft_isalpha(n) == 1 || n == '_')
		return (0);
	return (1);
}

/*
** Function identifies the variable name from the input string
*/

char	*get_variable_name(char *str, int loc)
{
	int		i;
	int		size;
	char	*name;

	i = 0;
	size = 0;
	while (validity_name(str[loc + size], size) == 0 && str[loc + size] != '\0')
		size++;
	if (size == 0)
		return (NULL);
	name = malloc(sizeof(char) * (size + 1));
	if (!name)
		return (NULL);
	name[size] = '\0';
	while (i < size)
	{
		name[i] = str[loc + i];
		i++;
	}
	return (name);
}

char	*get_value_from_envp(char *name, char **envp)
{
	int		i;
	int		s_name;
	char	*value;
	char	**temp;

	i = 0;
	s_name = ft_strlen(name);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(name, envp[i], s_name) == 0 && envp[i][s_name] == '=')
		{
			temp = ft_split(envp[i], '=');
			value = ft_strdup(temp[1]);
			free_string_array(temp);
			return (value);
		}
		i++;
	}
	return (NULL);
}

/*
**-------------------------------------------------------------------------
** Function replaces the variable $name with the correct variable value
*/

int	replace_dollar(char **str, int loc, t_data *data)
{
	char	*name;
	char	*node_val;

	if ((*str)[loc + 1] == '?')
		name = ft_strdup("?");
	else
		name = get_variable_name(*str, (loc + 1));
	if (name == NULL)
	{
		if ((*str)[loc + 1] == ' ' || (*str)[loc + 1] == '\0')
			node_val = ft_strdup("$");
		else
			node_val = ft_strdup("");
	}
	else
	{
		node_val = get_value_from_envp(name, data->envplist);
		if (node_val == NULL)
			node_val = ft_strdup("");
	}
	*str = insert_variable_value(*str, node_val, loc, ft_strlen(name));
	loc += ft_strlen(node_val) - 1;
	free(node_val);
	free(name);
	return (loc);
}

/*
**-------------------------------------------------------------------------
** Function detects the presence of $
*/

int	dollar_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
