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
	int	i;
	int	ret_i;

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
	char	*temp;
	int		ret_i;

//	printf("control\n");

	temp = malloc_string(ft_strlen(*str) - 2);
	ret_i = insert_val(*str, &temp, start, c);
	free(*str);
	*str = ft_strdup(temp);
	free(temp);
	return (ret_i);
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
				{
//					printf("control\n");
					j = replace_dollar(&str[i], j, data);
//					printf("replace[%d]: %s\n", j, str[i]);
				}
				else if (str[i][j] == '\"')
				{
					start = j;
					j++;
					while (str[i][j] != 34)
					{
						if (str[i][j] == '$' && validity_name(str[i][j + 1], (j + 1)) == 0)
						{
							j = replace_dollar(&str[i], j, data);
//							printf("str[%d][%d]: %s\n", i, j, str[i]);
						}
//						printf("j: %d\n", j);
						j++;
//						printf("j++: %d, str: %c\n", j, str[i][j]);

					}
//					printf("j: %d\n", j);
					j = replace_quotes1(&str[i], start, '\"');
//					printf("str[%d][%d]: %s\n", i, j, str[i]);
				}
				else if (str[i][j] == '\'')
					j = replace_quotes1(&str[i], j, '\'');
			}
			j++;
		}
		i++;
	}
	return (str);
}
