/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:44:25 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/04 16:27:08 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	just_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 32)
			return (1);
		i++;
	}
	return (0);
}

//-------------------------------------------------

static int	check_one_pair(char *str, int loc, char c)
{
	loc++;
	while (str[loc] != '\0' && str[loc] != c)
		loc++;
	return (loc);
}

static int	check_pairs(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			i = check_one_pair(str, i, '\"');
			if (str[i] == '\"')
				i++;
			else
				return (1);
		}
		else if (str[i] == '\'')
		{
			i = check_one_pair(str, i, '\'');
			if (str[i] == '\'')
				i++;
			else
				return (1);
		}
		else
			i++;
	}
	return (0);
}

/*
**-------------------------------------------------------------------------
** Function splits the input into individual tokens
** If syntax check and expansion go through, the tokens get placed
** into comand blocks to be used by the execve function
*/

t_list	*parse_blocks(char *str, t_data *data)
{
	char	**tokens;
	t_list	*cmd_blocks;

	tokens = ft_split_minishell(str, ' ');
	if (tokens != NULL)
	{
		if (check_syntax(tokens) == 1)
			error_syntax(tokens, data);
		else
		{
			tokens = expansion(tokens, data);
			cmd_blocks = set_cmd_blocks(tokens);
			free_string_array(tokens);
			return (cmd_blocks);
		}
	}
	return (NULL);
}

t_list	*parse_line(char *str, t_data *data)
{
	t_list	*cmd_blocks;

	cmd_blocks = NULL;
	if (just_spaces(str) == 0)
		return (NULL);
	if (check_pairs(str) == 1)
		error_quotes(data);
	else
		cmd_blocks = parse_blocks(str, data);
	return (cmd_blocks);
}
