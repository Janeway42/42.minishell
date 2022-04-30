#include "../includes/minishell.h"

/*
** Function returns a new string without the begining and end quotes
*/

char	*malloc_string(int size)
{
	char	*string;

	string = malloc(sizeof(char) * (size + 1));
	if (!string)
		exit_on_error("Error :", 1);
	string[size] = '\0';
	return (string);
}

//-------------------------------------------------

static int	insert_val(char *str, char **temp, int start, char c)
{
	int i;
	int ret_i;

	i = 0;
	while (i < start)
	{
		(*temp)[i] = str[i];
		i++;
	}
	while (str[start + 1] != c)
	{
		(*temp)[i] = str[start + 1];
		i++;
		start++;
	}
	ret_i = i;
	while (str[start + 2] != '\0')
	{
		(*temp)[i] = str[start + 2];
		i++;
		start++;
	}
	return (ret_i - 1);
}

int	replace_quotes1(char **str, int start, char c)
{
	char *temp;
	int ret_i;

	temp = malloc_string(ft_strlen(*str) - 2);
	ret_i = insert_val(*str, &temp, start, c);
	free(*str);
	*str = ft_strdup(temp);
	free(temp);
	return (ret_i);
	// int		i;
	// int		ret_i;
	// char	*temp;

	// i = 0;
	// temp = malloc_string(ft_strlen(*str) - 2);
	// while (i < start)
	// {
	// 	temp[i] = (*str)[i];
	// 	i++;
	// }
	// while ((*str)[start + 1] != c)
	// {
	// 	temp[i] = (*str)[start + 1];
	// 	i++;
	// 	start++;
	// }
	// ret_i = i;
	// while ((*str)[start + 2] != '\0')
	// {
	// 	temp[i] = (*str)[start + 2];
	// 	i++;
	// 	start++;
	// }
	// free(*str);
	// *str = ft_strdup(temp);
	// free(temp);
	// return (ret_i - 1);
}

/*
**-------------------------------------------------------------------------
** Function takes the string that contains $ and ~ and replaces
** the variable name with the value of the variable
*/

char	**expansion(char **str, t_data *data)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if (str[i][j] == '$' || str[i][j] == '~' || str[i][j] == '\'' || str[i][j] == '\"')
			{
				if (str[i][j] == '~' && j == 0 && (str[i][j + 1] == '\0' || str[i][j + 1] == '/'))
					j = home_value(&str[i], j, data->envplist);
				else if (str[i][j] == '$')
					j = replace_dollar(&str[i], j, data);
				else if (str[i][j] == '\"') // 34
				{
					start = j;
					j++;
					while (str[i][j] != 34)
					{
						if (str[i][j] == '$' && str[i][j + 1] != '=')
							j = replace_dollar(&str[i], j, data);
						j++;
					}
					j = replace_quotes1(&str[i], start, '\"');
				}
				else if (str[i][j] == '\'') // 39
					j = replace_quotes1(&str[i], j, '\'');
			}
			j++;
		}
		i++;
	}
	return (str);
}

// ------------------  OLD WORKING FUNCTION ---------------------------------------------------------------------------------------------------------------------------------

// char	**expansion(char **str, t_data *data)
// {
// 	int		i;
// 	int		j;
// 	int		start;
// 	int		lenght;
// 	char	*name;
// 	char	*node_val;

// 	i = 0;
// 	while (str[i] != NULL)
// 	{
// 		j = 0;
// 		while (str[i][j] != '\0')
// 		{
// 			if (str[i][j] == '$' || str[i][j] == '~' || str[i][j] == 39 || str[i][j] == 34)
// 			{
// 				if (str[i][j] == '~' && j == 0 && (str[i][j + 1] == '\0' || str[i][j + 1] == '/'))
// 				{
// 					str[i] = home_value(str[i], j, data->envplist);
					
// 					node_val = get_value_from_envp("HOME", data->envplist);
// 					j += ft_strlen(node_val);
// 				}
// 				else if (str[i][j] == '$')
// 				{
// 					if (str[i][j + 1] == '?')
// 						name = ft_strdup("?");
// 					else
// 						name = get_variable_name(str[i], j + 1);
// 					if (name == NULL)
// 					{
// 						if (str[i][j] == '$' && str[i][j + 1] == '\0')
// 							node_val = "$";
// 						else
// 							node_val = "";
// 					}
// 					else
// 					{
// 						node_val = get_value_from_envp(name, data->envplist);
// 						if (node_val == NULL)
// 							node_val = "";
// 					}
// 					str[i] = insert_variable_value(str[i], node_val, j, ft_strlen(name));
// 					j += ft_strlen(node_val) - 1;
// 					free(name);
// 				}
// 				else if (str[i][j] == '\"')
// 				{
// 					start = j;
// 					j++;
// 					while (str[i][j] != 34)
// 					{
// 						if (str[i][j] == '$' && str[i][j + 1] != '=')
// 						{
// 							if (str[i][j + 1] == '?')
// 								name = ft_strdup("?");
// 							else
// 								name = get_variable_name(str[i], j + 1);
// 							if (name == NULL)
// 							{
// 								if (str[i][j] == '$' && str[i][j + 1] == 34)
// 									node_val = "$";
// 								else
// 									node_val = "";
// 							}
// 							else
// 							{
// 								node_val = get_value_from_envp(name, data->envplist);
// 								if (node_val == NULL)
// 									node_val = "";
// 							}
// 							str[i] = insert_variable_value(str[i], node_val, j, ft_strlen(name));
// 							j += ft_strlen(node_val) - 1;
// 							free(name);
// 						}
// 						j++;
// 					}
// 					lenght = get_lenght(str[i], start, 34);
// 					str[i] = replace_quotes(str[i], start, 34);
// 					j = start + lenght - 3;
// 				}
// 				else if (str[i][j] == '\'')
// 				{
// 					lenght = get_lenght(str[i], j, 39);
// 					str[i] = replace_quotes(str[i], j, 39);
// 					j = j + lenght - 3;
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (str);
// }


// ------------------  OLD TEST ---------------------------------------------------------------------------------------------------------------------------------

// char *malloc_string(int size)
// {
// 	char *string;

// 	string = malloc(sizeof(char) * (size + 1));
// 	if (!string)
// 		return (NULL);   // return error_malloc ????????????????  ////////////////////
// 	string[size] = '\0';
// 	return (string);
// }

// int	replace_quotes1(char **str, int start, char c)
// {
// 	int		i;
// 	char	*temp;

// 	i = 0;
// 	temp = malloc_string(ft_strlen(*str) - 2);
// 	while (i < start)
// 	{
// 		temp[i] = (*str)[i];
// 		i++;
// 	}
// 	start++;
// 	while ((*str)[start] != c)
// 	{
// 		temp[i] = (*str)[start];
// 		i++;
// 		start++;
// 	}
// 	if ((*str)[start] == c)
// 		start++;
// 	while ((*str)[start] != '\0')
// 	{
// 		temp[i] = (*str)[start];
// 		i++;
// 		start++;
// 	}
// 	free(*str);
// 	*str = ft_strdup(temp);
// 	free(temp);
// 	return (i - 1);
// }

// char *rewrite_function(char *str, char *node_val, char *temp, int step1, int step2)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (i < step1)
// 	{
// 		temp[i] = (str[i]);
// 		i++;
// 	}
// 	while (i < step2)
// 	{
// 		temp[i] = node_val[j];
// 		i++;
// 		j++;
// 	}
// 	j = 0;
// 	while (str[step1 + 1 + j] != '\0')
// 	{
// 		temp[i + j] = str[step1, + 1 + j];
// 		j++;
// 	}
// 	return (temp);
// }

// int	home_value1(char **str, int loc, char **envplist)
// {
// 	int node_lenght;
// 	int i;
// 	int j;
// 	char *node_val;
// 	char *temp;

// 	i = 0;
// 	j = 0;
// 	node_val = get_value_from_envp("HOME", envplist);
// 	node_lenght = ft_strlen(node_val);
// 	temp = malloc_string((ft_strlen(*str) - 1) + node_lenght + 1);
// 	while (i < loc)
// 	{
// 		temp[i] = (*str)[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (i < (loc + node_lenght))
// 	{
// 		temp[i] = node_val[j];
// 		i++;
// 		j++;
// 	}
// 	j = 0;
// 	while ((*str)[loc + 1 + j] != '\0')
// 	{
// 		temp[i + j] = (*str)[loc + 1 + j];
// 		j++;
// 	}
// 	free(*str);
// 	*str = ft_strdup(temp);
// 	free(temp);
// 	return (i + j - 1);
// }

// char	**expansion(char **str, t_data *data)
// {
// 	int		i;
// 	int		j;
// 	int		start;

// 	i = 0;
// 	while (str[i] != NULL)
// 	{
// 		j = 0;
// 		while (str[i][j] != '\0')
// 		{
// 			if (str[i][j] == '$' || str[i][j] == '~' || str[i][j] == '\'' || str[i][j] == '\"')
// 			{
// 				if (str[i][j] == '~' && j == 0 && (str[i][j + 1] == '\0' || str[i][j + 1] == '/'))
// 					j = home_value1(&str[i], j, data->envplist);
// 				else if (str[i][j] == '$')
// 					j = replace_dollar(&str[i], j, data);
// 				else if (str[i][j] == '\"')
// 				{
// 					start = j;
// 					j++;
// 					while (str[i][j] != 34)
// 					{
// 						if (str[i][j] == '$' && str[i][j + 1] != '=')
// 							j = replace_dollar(&str[i], j, data);
// 						j++;
// 					}
// 					j = replace_quotes1(&str[i], start, '\"');
// 				}
// 				else if (str[i][j] == '\'')
// 					j = replace_quotes1(&str[i], start, '\'');
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (str);
// }
