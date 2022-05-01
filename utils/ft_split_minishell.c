/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_minishell.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:53:48 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 17:54:19 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**-------------------------------------------------------------------------
** get the lenght of the string to be created
** Single quotation ASCII = 39, Double quotation ASCII = 34
*/

int	compare_operators(char *str, int loc)
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

static int	string_lenght(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (compare_operators(str, i) == 1)
			return (i = 2);
		else if (str[i] == '|' || compare_operators(str, i) == 2)
			return (i = 1);
		else
		{
			while (str[i] != c && str[i] != '|' && str[i] != '<'
				&& str[i] != '>' && str[i] != '\0')
			{
				if (str[i] == '\'')
					i = run_through_quotes(str, i, '\'');
				else if (str[i] == '\"')
					i = run_through_quotes(str, i, '\"');
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
