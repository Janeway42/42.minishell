#include "../includes/minishell.h"

/*
**-------------------------------------------------------------------------
** get the number of strings to be created
** Single quotation ASCII = 39, Double quotation ASCII = 34
*/

int	check_operator(char c)
{
	if (c == '|' || c == '<' || c == '>'
		|| c == 39 || c == 34 || c == 32)
		return (1);
	return (0);
}

static int	run_though_quotes(char *str, int loc)
{
	if (str[loc] == 39)
	{
		loc++;
		while (str[loc] != '\0' && str[loc] != 39)
			loc++;
		if (str[loc] == 39)
			loc++;
	}
	if (str[loc] == 34)
	{
		loc++;
		while (str[loc] != '\0' && str[loc] != 34)
			loc++;
		if (str[loc] == 34)
			loc++;
	}
	return (loc);
}

static int	run_through_elem(char *str, int loc)
{
	if (str[loc] == 39 || str[loc] == 34)
			loc = run_though_quotes(str, loc);
	else if (str[loc] == '<' || str[loc] == '>')
	{
		if ((str[loc] == '<' && str[loc + 1] == '<')
			|| (str[loc] == '>' && str[loc + 1] == '>'))
			loc += 2;
		else if ((str[loc] == '<' && str[loc + 1] != '<')
			|| (str[loc] == '>' && str[loc + 1] != '>'))
			loc++;
	}
	else if (str[loc] == '|' )
		loc++;
	return (loc);
}

int	count_strings(char *str, char c)
{
	int	i;
	int	nr_strings;

	i = 0;
	nr_strings = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		if (str[i] == '\0')
			return (nr_strings);
		if (check_operator(str[i]) == 1)
		{
			i = run_through_elem(str, i);
			nr_strings++;
		}
		else
		{
			while (str[i] != '\0' && check_operator(str[i]) == 0)
					i++;
			nr_strings++;
		}
	}
	return (nr_strings);
}
