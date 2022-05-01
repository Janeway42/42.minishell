/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_syntax.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa&hman@student.codam.nl>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 14:53:48 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 14:56:19 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_syntax_pipe(char **str)
{
	int	i;

	i = 0;
	if (ft_strcmp(str[0], "|") == 0)
		return (1);
	while (str[i + 1] != NULL)
	{
		if (ft_strcmp(str[i], "|") == 0 && ft_strcmp(str[i + 1], "|") == 0)
			return (1);
		else
			i++;
	}
	if (ft_strcmp(str[i], "|") == 0)
		return (1);
	return (0);
}

//-------------------------------------------------

static int	check_operators(char **str, int i)
{
	if (str[i + 1] == NULL)
		return (1);
	if (ft_strcmp(str[i + 1], "<") == 0)
		return (1);
	if (ft_strcmp(str[i + 1], ">") == 0)
		return (1);
	if (ft_strcmp(str[i + 1], "<<") == 0)
		return (1);
	if (ft_strcmp(str[i + 1], ">>") == 0)
		return (1);
	return (0);
}

static int	check_rest_syntax(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		while (str[i] != NULL && ft_strcmp(str[i], "|") != 0)
		{
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
				return (0);
		}
		i++;
	}
	return (0);
}

//-------------------------------------------------

int	last_pipe(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_strcmp(str[i], "|") == 0 && str[i + 1] == NULL)
			return (1);
		i++;
	}
	return (0);
}

/*
**-------------------------------------------------------------------------
** Check first whether there are double '|'
** then check for the rest of the syntax
** and lastly for multiline
*/

int	check_syntax(char **str)
{
	if (check_syntax_pipe(str) == 1)
		return (1);
	if (check_rest_syntax(str) == 1)
		return (1);
	if (last_pipe(str) == 1)
		return (1);
	return (0);
}
