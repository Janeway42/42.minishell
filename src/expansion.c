#include "../includes/minishell.h"

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		k;
	int		size;
	char	*temp;

	i = 1;
	j = 0;
	k = 0;
	size = ft_strlen(str);
	temp = malloc(sizeof(char) * (size - 1));
	if (!temp)
		return (NULL);
	temp[size - 2] = '\0';
	while (j < size - 2)
	{
		temp[j] = str[i];
		j++;
		i++;
	}
	free(str);
	str = ft_strdup(temp);
	free(temp);
	return (str);
}

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

int	validity_name(char c, int location) // alpha digit and underscore and the first char can't be a digit
{
	int n;

	n = (int) c;
	if (location == 0 && ft_isdigit(c) == 1)
		return (1);
	if (ft_isdigit(c) == 1 || ft_isalpha(n) == 1 || n == '_')
		return (0);
	return (1);
}

char	*get_variable_name(char *str, int location)
{
	int		i;
	int		size;
	char	*name;

	i = 0;
	size = 0;

	while (validity_name(str[location + size], size) == 0 && str[location + size] != '\0')
		size++;
	if (size == 0)
		return (NULL);

	name = malloc(sizeof(char) * (size + 1));
	if (!name)
		return (NULL);
	name[size] = '\0';
	while (i < size)
	{
		name[i] = str[location + i];
		i++;
	}
	return (name);
}

char	*insert_name(char *str, char *value, int location, int name_size)
{
	int		i;
	int		j;
	int		size;
	int		lenght_val;
	char	*temp;

	i = 0;
	j = 0;
	lenght_val = ft_strlen(value);
	if (lenght_val == 0)
	{
		size = ft_strlen(str) - name_size - 1;
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
			temp[i] = str[i + name_size + 1]; // i + name size + $
			i++;
		}
	}
	else
	{
		size = ft_strlen(str) - name_size + lenght_val - 1; // lenght str - name size + value lenght - $
		temp = malloc(sizeof(char) * (size + 1));
		if (!temp)
			return (NULL);
		temp[size] = '\0';
		while (i < location)
		{
			temp[i] = str[i];
			i++;
		}
		while (i < (location + lenght_val))
		{
			temp[i] = value[j];
			i++;
			j++;
		}
		j = 0;
		while (str[location + name_size + 1 + j] != '\0') // + 1 is the $ sign 
		{
			temp[i] = str[location + name_size + 1 + j];
			i++;
			j++;
		}
	}
	free(str);
	str = ft_strdup(temp);
	free(temp);
	return (str);
}

char	*check_name_in_envp(char *name, t_env	*envplist)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = envplist;
	while (temp != NULL)
	{
		if (ft_strncmp(name, temp->key, ft_strlen(name)) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

char	*replace_dollar(char *str, t_env	*envplist)
{
	int		i;
	char	*name;
	char	*node_value;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			name = get_variable_name(str, i + 1);
			if (name == NULL)
				node_value = "";
			else
			{
				node_value = check_name_in_envp(name, envplist);
				if (node_value == NULL)
					node_value = "";
			}
			str = insert_name(str, node_value, i, ft_strlen(name));
			i += ft_strlen(node_value) - 1;
		}
		i++;
	}
	return (str);
}

char	**expansion(char **str, t_env	*envplist)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] == 34) // double quotation
		{
			str[i] = remove_quotes(str[i]);
			if (dollar_sign(str[i]) == 1)
				str[i] = replace_dollar(str[i], envplist);
		}
		if (str[i][0] == 39)  // single quotaton
			str[i] = remove_quotes(str[i]);
		if (dollar_sign(str[i]) == 1)
			str[i] = replace_dollar(str[i], envplist);
		i++;
	}
	return (str);
}
