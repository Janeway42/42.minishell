#include "../includes/minishell.h"

static int	count_strings(char *str, char c)
{
	int	i;
	int	nr_strings;

	i = 0;
	nr_strings = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && str[i + 1] == '\0')
		{
			nr_strings++;
			i++;
		}

		while (str[i] == c)
			i++;

		if (str[i] == 39 || str[i] == 34)
		{
			if (str[i] == 39) // single
			{
				i++;
				while (str[i] != 39)
					i++;
				if (str[i] == 39)
					i++;
				nr_strings++;
			}
			else if (str[i] == 34) // double
			{
				i++;
				while (str[i] != 34)
					i++;
				if (str[i] == 34)
					i++;
				nr_strings++;
			}
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
			{
				nr_strings++;
				i++;
				i++;
			}
			else if ((str[i] == '<' && str[i + 1] != '<') || (str[i] == '>' && str[i + 1] != '>'))
			{
				nr_strings++;
				i++;
			}
		}
		else if (str[i] == '|' )
		{
			nr_strings++;
			i++;
		}
		else if (str[i] != c && str[i + 1] == c)
		{
			nr_strings++;
			i++;
		}
		else
		{
			while (str[i] != '\0' && str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != 39 && str[i] != 34 && str[i] != 32)
				i++;
			nr_strings++;
		}
	}
	return (nr_strings);
}

static int	lenght_quotes(char *str)
{
	int	lenght;

	lenght = 0;
	lenght++;
	while (str[lenght] != 39)
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
		if (str[i] == 39) // single
			return (lenght_quotes(str));
		else if (str[i] == 34) // double
			return (lenght_quotes(str));
		else if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
			return (i = 2);
		else if (str[i] == '|' || (str[i] == '<' && str[i + 1] != '<') 
				|| (str[i] == '>' && str[i + 1] != '>'))
			return (i = 1);
		else
		{
			while (str[i] != c && str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != '\0')
				i++;
			return (i);
		}
	}
	return (i);
}

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

static char **fill(char *str, int nr_strings, char c, char **result)
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
	result = malloc(sizeof(char **) * (nr_strings + 1));
	if (!result)
		return (NULL);
	result[nr_strings] = NULL;
	result = fill(str, nr_strings, c, result);
	return (result);
}
