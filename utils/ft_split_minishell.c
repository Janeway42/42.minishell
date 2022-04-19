#include "../includes/minishell.h"

/*
**-------------------------------------------------------------------------
** get the lenght of the string to be created
** Single quotation ASCII = 39, Double quotation ASCII = 34
*/

static int	lenght_quotes(char *str)
{
	int	lenght;

	lenght = 0;
	lenght++;
	while (str[lenght] != '\0' && str[lenght] != 39)
		lenght++;
	if (str[lenght] == 39)
		lenght++;
	return (lenght);
}

static int	string_lenght(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39)
			return (lenght_quotes(str));
		else if (str[i] == 34)
			return (lenght_quotes(str));
		else if ((str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>'))
			return (i = 2);
		else if (str[i] == '|' || (str[i] == '<' && str[i + 1] != '<')
			|| (str[i] == '>' && str[i + 1] != '>'))
			return (i = 1);
		else
		{
			while (str[i] != c && str[i] != '|' && str[i] != '<'
				&& str[i] != '>' && str[i] != '\0')
				i++;
			return (i);
		}
	}
	return (i);
}

/*
**-------------------------------------------------------------------------
*/

char	**free_array(char **array, int position)
{
	int	i;

	i = 0;
	while (i < position)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static char	**fill(char *str, int nr_strings, char c, char **result)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	while (i < nr_strings)
	{
		while (*str == c && *str != 39 && *str != 34)
			str++;
		size = string_lenght(str, c);
		result[i] = malloc(sizeof(char) * (size + 1));
		if (!result[i])
			return (free_array(result, i));
		result[i][size] = '\0';
		j = 0;
		while (j < size)
		{
			result[i][j] = *str;
			str++;
			j++;
		}
		printf("str[%d]: %s\n", i, result[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split_minishell(char *str, char c)
{
	int		nr_strings;
	char	**result;

	nr_strings = count_strings(str, c);
	printf("nr_strings: %d\n", nr_strings);
	result = malloc(sizeof(char *) * (nr_strings + 1));
	if (!result)
		return (NULL);
	result[nr_strings] = NULL;
	result = fill(str, nr_strings, c, result);
	return (result);
}
