#include "../includes/minishell.h"

/*
**-------------------------------------------------------------------------
** get the lenght of the string to be created
** Single quotation ASCII = 39, Double quotation ASCII = 34
*/

int compare_operators(char *str, int loc)   // too many functions 
{
	if (str[loc] == '<' && str[loc + 1] == '<')
		return (1);
	if (str[loc] == '>' && str[loc + 1] == '>')
		return (1);
	if (str[loc] == '<' && str[loc + 1] != '<')
		return (2);
	if (str[loc] == '>' && str[loc + 1] != '>')
		return (2);
	return (0);
}

static int	lenght_quotes(char *str, int loc, char c) // duplicate with quote lenght 
{
	loc++;
	while (str[loc] != '\0' && str[loc] != c)
		loc++;
	if (str[loc] == c)
		loc++;
	return (loc);
}

static int	string_lenght(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (compare_operators(str, i) == 1)
//		if ((str[i] == '<' && str[i + 1] == '<')
//			|| (str[i] == '>' && str[i + 1] == '>'))
			return (i = 2);
		else if (str[i] == '|' || compare_operators(str, i) == 2)
//		else if (str[i] == '|' || (str[i] == '<' && str[i + 1] != '<')
//			|| (str[i] == '>' && str[i + 1] != '>'))
			return (i = 1);
		else
		{
			while (str[i] != c && str[i] != '|' && str[i] != '<'
				&& str[i] != '>' && str[i] != '\0')
			{
				if (str[i] == '\'')
					i = lenght_quotes(str, i, '\'');
				else if (str[i] == '\"')
					i = lenght_quotes(str, i, '\"');
				else
					i++;
			}
			return (i);
		}
	}
	return (i);
}

//-------------------------------------------------

static char	**fill(char *str, int nr_strings, char c, char **result)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	while (i < nr_strings)
	{
		while (*str == c && *str != '\'' && *str != '\"')
			str++;
		size = string_lenght(str, c);
		result[i] = malloc(sizeof(char) * (size + 1));
		if (!result[i])
			return (free_array_ft_split(result, i));
		result[i][size] = '\0';
		j = 0;
		while (j < size)
		{
			result[i][j] = *str;
			str++;
			j++;
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

/*
**-------------------------------------------------------------------------
*/

char	**ft_split_minishell(char *str, char c)
{
	int		nr_strings;
	char	**result;

	nr_strings = count_strings(str, c);
	result = malloc(sizeof(char *) * (nr_strings + 1));
	if (!result)
		return (NULL);
	result[nr_strings] = NULL;
	result = fill(str, nr_strings, c, result);
	return (result);
}
