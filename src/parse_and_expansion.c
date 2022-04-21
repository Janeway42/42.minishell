#include "../includes/minishell.h"

/*
** Function returns a new string without the begining and end quotes
*/

// static char	*remove_quotes(char *str)
// {
// 	int		i;
// 	int		size;
// 	char	*temp;

// 	i = 0;
// 	size = ft_strlen(str) - 2;
// 	temp = malloc(sizeof(char) * (size + 1));
// 	if (!temp)
// 		return (NULL);
// 	temp[size] = '\0';
// 	while (i < size)
// 	{
// 		temp[i] = str[i + 1];
// 		i++;
// 	}
// 	free(str);
// 	str = ft_strdup(temp);
// 	free(temp);
// 	return (str);
// }

char *replace_quotes(char *str, int start)
{
	int i;
	int size;
	char *temp;
	
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

	if (str[start] == 34)
	{
		start++;
		while (str[start] != 34)
		{
			temp[i] = str[start];
			i++;
			start++;
		}
		if (str[start] == 34)
			start++;
		while (str[start] != '\0')
		{
			temp[i] = str[start];
			i++;
			start++;
		}
	}
	else if (str[start] == 39)
	{
		start++;
		while (str[start] != 39)
		{
			temp[i] = str[start];
			i++;
			start++;
		}
		if (str[start] == 39)
			start++;
		while (str[start] != '\0')
		{
			temp[i] = str[start];
			i++;
			start++;
		}
	}

	free(str);
	str = ft_strdup(temp);
	free(temp);
	return (str);
}

/*
** Function takes the string that contains $ and replaces
** the variable name with the value of the variable
** double quotation (ascii 34) allows for the presence of variables
** single quotation (ascii 39) transforms all in char
*/

// char	**expansion(char **str, t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != NULL)
// 	{
// 		if (str[i][0] == 34)
// 		{
// 			str[i] = remove_quotes(str[i]);
// 			if (dollar_sign(str[i]) == 1)
// 				str[i] = replace_dollar(str[i], data->envplist);
// 		}
// 		if (str[i][0] == 39)
// 			str[i] = remove_quotes(str[i]);
// 		if (dollar_sign(str[i]) == 1)
// 			str[i] = replace_dollar(str[i], data->envplist);
// 		i++;
// 	}
// 	return (str);
// }

//--------------------------------------------------------------

int	get_lenght_double(char *str, int loc)
{
	int lenght;

	lenght = 0;
	if (str[loc + lenght] == 34)
		lenght++;
	while (str[loc + lenght] != 34)
		lenght++;
	if (str[loc + lenght] == 34)
		lenght++;
	return (lenght);
}

int get_lenght_single(char *str, int loc)
{
	int lenght;

	lenght = 0;
	if (str[loc + lenght] == 39)
		lenght++;
	while (str[loc + lenght] != 39)
		lenght++;
	if (str[loc + lenght] == 39)
		lenght++;
	return (lenght);
}

// if quotes without $ just copy the text
// if double quotes and $ then replace $ 
// if single quotes and $ then copy as it is


char **expansion(char **str, t_data *data)
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
			if (str[i][j] == '$' || str[i][j] == 39 || str[i][j] == 34)
			{
				if (str[i][j] == '$')
				{
					if (str[i][j + 1] == '?')
						name = "?";
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
								name = "?";
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
							str[i] = insert_variable_value(str[i], node_val, j, ft_strlen(name));
							j += ft_strlen(node_val) - 1;
						}
						j++;
					}
					lenght = get_lenght_double(str[i], start);
					str[i] = replace_quotes(str[i], start);
					j = start + lenght - 3;
				}
				else if (str[i][j] == 39) // single
				{
					lenght = get_lenght_single(str[i], j);
					str[i] = replace_quotes(str[i], j);
					j = j + lenght - 3;
				}
			}
			j++;
		}
		i++;
	}
	return (str);
}





//--------------------------------------------

static int	check_unclosed_quotes(char *str)
{
	int i;
	int one;
	int two;
	
	i = 0;
	one = 0;
	two = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39) // single 
		{
			if (one == 0)
				one = 1;
			else if (one == 1)
				one = 0;
		}
		if (str[i] == 34) // double 
		{
			if (two == 0)
				two = 1;
			else if (two == 1)
				two = 0;
		}
		i++;
	}
	if (one == 1 || two == 1)
		return (1);
	return (0);
}

/*
**-------------------------------------------------------------------------
** Function splits the input into individual tokens
** If syntax check and expansion go through, the tokens get placed
** into comand blocks to be used by the execve function
*/

t_list	*parse_line(char *str, t_data *data)
{
	char	**tokens;
	t_list	*cmd_blocks;

	if (check_unclosed_quotes(str) == 1)
		printf("syntax error: unclosed quotes\n");
	else
	{
		tokens = ft_split_minishell(str, ' ');
		if (tokens != NULL)
		{
			if (check_syntax(tokens) == 1)
				error_syntax(&tokens);
			else
			{
				tokens = expansion(tokens, data);
				print_token(tokens); // remove once completed !!!!!!!!!
				cmd_blocks = set_cmd_blocks(tokens);
				print_cmd_blocks(cmd_blocks);
				free_double(&tokens);
				return (cmd_blocks);
			}
		}
	}
	return (NULL);
}
