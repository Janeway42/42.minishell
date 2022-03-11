#include "../includes/minishell.h"

static int	check_syntax_pipe(char **str)
{
	int	i;

	i = 0;
	while (str[i + 1] != NULL)
	{
		if (ft_strcmp(str[i], "|") == 0 && ft_strcmp(str[i + 1], "|") == 0)
			return (1);
		else
			i++;
	}
	return (0);
}

static int	check_operators(char **str, int i)
{
	if (ft_strcmp(str[i + 1], "<") == 0)
		return (1);
	if (ft_strcmp(str[i + 1], ">") == 0)
		return (1);
	if (ft_strcmp(str[i + 1], "<<") == 0)
		return (1);
	if (ft_strcmp(str[i + 1], ">>") == 0)
		return (1);
	if (*str[i + 1] == '\0')
		return (1);
	return (0);
}

static int	check_rest_syntax(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		printf("str[i]: %s\n", str[i]);
		while (str[i] != NULL && ft_strcmp(str[i], "|") != 0)
		{
			printf("str[i inside]: %s\n", str[i]);
			if (ft_strcmp(str[i], "<") == 0 && check_operators(str, i) == 1)
				return (1);
			if (ft_strcmp(str[i], ">") == 0 && check_operators(str, i) == 1)
				return (1);
			if (ft_strcmp(str[i], "<<") == 0 && check_operators(str, i) == 1)
				return (1);
			if (ft_strcmp(str[i], ">>") == 0 && check_operators(str, i) == 1)
				return (1);
			i++;
			if (str[i] == NULL)
				return (0) ;
		}
		i++;
	}
	return (0);
}

int	check_syntax(char **str)
{
	if (check_syntax_pipe(str) == 1) // first if there are double '|'
		return (1);
	if (check_rest_syntax(str) == 1)// then the rest of the syntax
		return (1);
	return (0);
}
