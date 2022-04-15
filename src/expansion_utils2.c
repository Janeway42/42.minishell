#include "../includes/minishell.h"

/*
** Function creates a new string without the $variable_name
** size of the new str is (ft_strlen(str) - size of the name - $)
** copies first the bit before $ and then the bit after the value name
*/

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
** Function creates a new string that replaces the $variable_name
** with the variable value from environment
** new str size = (ft_strlen(str) - (name size + $) + value)
** copies first the bit before $, then the value,
** and last what is left after the value name
*/

static char	*non_null_value(int name_size, int location, char *str, char *value)
{
	int		i;
	int		j;
	int		size;
	int		lenght_val;
	char	*temp;

	i = 0;
	lenght_val = ft_strlen(value);
	size = ft_strlen(str) - (name_size + 1) + lenght_val;
	temp = malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (NULL);
	temp[size] = '\0';
	while (i < location)
	{
		temp[i] = str[i];
		i++;
	}
	j = 0;
	while (i < (location + lenght_val))
	{
		temp[i] = value[j];
		i++;
		j++;
	}
	j = 0;
	while (str[location + (name_size + 1) + j] != '\0')
	{
		temp[i + j] = str[location + name_size + 1 + j];
		j++;
	}
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
		temp = null_value(size_name, loc, str);
	else
		temp = non_null_value(size_name, loc, str, value);
	free(str);
	str = ft_strdup(temp);
	free(temp);
	return (str);
}
