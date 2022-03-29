#include "../includes/minishell.h"

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
			free_double(&temp);
			return (value);
		}
		i++;
	}
	return (NULL);
}

char	*replace_dollar(char *str, char **envplist)
{
	int		i;
	char	*name;
	char	*node_val;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			name = get_variable_name(str, i + 1);
			if (name == NULL)
				node_val = "";
			else
			{
				node_val = get_value_from_envp(name, envplist);
				if (node_val == NULL)
					node_val = "";
			}
			str = insert_variable_value(str, node_val, i, ft_strlen(name));
			i += ft_strlen(node_val) - 1;
		}
		i++;
	}
	return (str);
}

/*
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

/*
** Function takes the string that contains $ and replaces
** the variable name with the value of the variable
** double quotation (ascii 34) allows for the presence of variables
** single quotation (ascii 39) transforms all in char
*/

char	**expansion(char **str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] == 34)
		{
			str[i] = remove_quotes(str[i]);
			if (dollar_sign(str[i]) == 1)
				str[i] = replace_dollar(str[i], data->envplist);
		}
		if (str[i][0] == 39)
			str[i] = remove_quotes(str[i]);
		if (dollar_sign(str[i]) == 1)
			str[i] = replace_dollar(str[i], data->envplist);
		i++;
	}
	return (str);
}
