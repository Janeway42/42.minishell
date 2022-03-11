#include "../includes/minishell.h"

static int	count_strings(char *str, char c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && str[i + 1] == '\0')
		{
			size++;
			i++;
		}
		else
		{
			if (str[i] == 39) // single
			{	i++;
				while (str[i] != 39)
					i++;
				if (str[i] == 39)
					i++;
				size++;
			}
			else if (str[i] == 34) // double
			{
				i++;
				while (str[i] != 34)
					i++;
				if (str[i] == 34)
					i++;
				size++;
			}

			else if ((str[i] == '<' || str[i] == '>'))
			{
				if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
				{
					size++;
					i++;
					i++;
				}
				else if ((str[i] == '<' && str[i + 1] != '<') || (str[i] == '>' && str[i + 1] != '>'))
				{
					size++;
					i++;
				}
			}
			else if (str[i] == '|' )
			{
				size++;
				i++;
			}

			else if (str[i] != c && str[i + 1] == c)
			{
				size++;
				i++;
			}

			else
				i++;
		}
	}
	return (size);
}

static int	string_lenght(char *str, char c)
{
	int	i;
	int	lenght;

	i = 0;
	lenght = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39) // single
			{
				i++;
				lenght++;
				while (str[i] != 39)
				{
					lenght++;
					i++;
				}
				if (str[i] == 39)
				{
					lenght++;
					i++;
				}
				return(lenght);
			}
			else if (str[i] == 34) // double
			{
				i++;
				lenght++;
				while (str[i] != 34)
				{
					lenght++;
					i++;
				}
				if (str[i] == 34)
				{
					lenght++;
					i++;
				}
				return(lenght);
			}
			else if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
				return (lenght = 2);
			else if ((str[i] == '<' && str[i + 1] != '<') || (str[i] == '>' && str[i + 1] != '>'))
				return (lenght = 1);
			else if (str[i] == '|' )
				return (lenght = 1);
			else
			{
				while (str[i] != c && str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != '\0')
				{
					lenght++;
					i++;
				}
				return (lenght);
			}
	}
	return (lenght);
}

void	*free_array(char **array, int position)
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

char **ft_split_minishell(char *str, char c)
{
	int		nr_strings;
	char	**result;

	nr_strings = count_strings(str, c);
	result = malloc(sizeof(char **) * (nr_strings + 1));
	if (!result)
		return (NULL);
//	result[nr_strings] = NULL;
	result = fill(str, nr_strings, c, result);
	return (result);
}

