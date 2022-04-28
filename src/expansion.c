#include "../includes/minishell.h"

/*
** Function returns a new string without the begining and end quotes
*/

char	*replace_quotes(char *str, int start, char c)
{
	int		i;
	int		size;
	char	*temp;

	i = 0;
	size = ft_strlen(str) - 2;
	temp = malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (NULL);
	temp[size] = '\0';
	while (i < start)
	{
		temp[i] = str[i];
		i++;
	}
	start++;
	while (str[start] != c)
	{
		temp[i] = str[start];
		i++;
		start++;
	}
	if (str[start] == c)
		start++;
	while (str[start] != '\0')
	{
		temp[i] = str[start];
		i++;
		start++;
	}
	free(str);
	str = ft_strdup(temp);
	free(temp);
	return (str);
}

int	get_lenght(char *str, int loc, char c)
{
	int	lenght;

	lenght = 0;
	if (str[loc + lenght] == c)
		lenght++;
	while (str[loc + lenght] != c)
		lenght++;
	if (str[loc + lenght] == c)
		lenght++;
	return (lenght);
}

/*
** Function takes the string that contains $ and replaces
** the variable name with the value of the variable
** double quotation (ascii 34) allows for the presence of variables
** single quotation (ascii 39) transforms all in char
*/

char	**expansion(char **str, t_data *data)
{
	int		i;
	int		j;
	int		start;
	int		lenght;
	char	*name;
	char	*node_val;

	i = 0;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if (str[i][j] == '$' || str[i][j] == '~' || str[i][j] == 39 || str[i][j] == 34)
			{
				if (str[i][j] == '~' && j == 0 && (str[i][j + 1] == '\0' || str[i][j + 1] == '/'))
				{
					str[i] = home_value(str[i], j, data->envplist);
					j += ft_strlen(node_val) - 1;
				}
				else if (str[i][j] == '$')
				{
					if (str[i][j + 1] == '?')
						name = ft_strdup("?");
					else
						name = get_variable_name(str[i], j + 1);
					if (name == NULL)
					{
						if (str[i][j] == '$' && str[i][j + 1] == '\0')
							node_val = "$";
						else
							node_val = "";
					}
					else
					{
						node_val = get_value_from_envp(name, data->envplist);
						if (node_val == NULL)
							node_val = "";
					}
					str[i] = insert_variable_value(str[i], node_val, j, ft_strlen(name));
					j += ft_strlen(node_val) - 1;
					free(name);
				}
				else if (str[i][j] == 34) // double 
				{
					start = j;
					j++;
					while (str[i][j] != 34)
					{
						if (str[i][j] == '$' && str[i][j + 1] != '=')
						{
							if (str[i][j + 1] == '?')
								name = ft_strdup("?");
							else
								name = get_variable_name(str[i], j + 1);
							if (name == NULL)
							{
								if (str[i][j] == '$' && str[i][j + 1] == 34)
									node_val = "$";
								else
									node_val = "";
							}
							else
							{
								node_val = get_value_from_envp(name, data->envplist);
								if (node_val == NULL)
									node_val = "";
							}
//							printf("node_val: %s\n", node_val);
							str[i] = insert_variable_value(str[i], node_val, j, ft_strlen(name));
//							printf("str[%d]: %s\n", i, str[i]);
							j += ft_strlen(node_val) - 1;
							free(name);
						}
						j++;
					}
					lenght = get_lenght(str[i], start, 34);
					str[i] = replace_quotes(str[i], start, 34);
					j = start + lenght - 3;
				}
				else if (str[i][j] == 39) // single
				{
					lenght = get_lenght(str[i], j, 39);
					str[i] = replace_quotes(str[i], j, 39);
					j = j + lenght - 3;
				}
			}
			j++;
		}
		i++;
	}
	return (str);
}


