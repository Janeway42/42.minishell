/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa&hman@student.codam.nl>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 14:53:48 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 15:12:05 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	insert_val(char *str, char **temp, int start, char c)
{
	int	i;
	int	ret_i;

	i = 0;
	while (i < start)
	{
		(*temp)[i] = str[i];
		i++;
	}
	while (str[start + 1] != c)
	{
		(*temp)[i] = str[start + 1];
		i++;
		start++;
	}
	ret_i = i;
	while (str[start + 2] != '\0')
	{
		(*temp)[i] = str[start + 2];
		i++;
		start++;
	}
	return (ret_i - 1);
}

int	replace_quotes1(char **str, int start, char c)
{
	char	*temp;
	int		ret_i;

	temp = malloc_string(ft_strlen(*str) - 2);
	ret_i = insert_val(*str, &temp, start, c);
	free(*str);
	*str = ft_strdup(temp);
	free(temp);
	return (ret_i);
}

/*
**-------------------------------------------------------------------------
** Function takes the string that contains $ and ~ and replaces
** the variable name with the value of the variable
*/

static int	expand_double_quote(char **str, int loc, t_data *data)
{
	int	start;

	start = loc;
	loc++;
	while ((*str)[loc] != '\"')
	{
		if ((*str)[loc] == '$'
			&& validity_name((*str)[loc + 1], (loc + 1)) == 0)
			loc = replace_dollar(str, loc, data);
		loc++;
	}
	loc = replace_quotes1(str, start, '\"');
	return (loc);
}

static int	if_expansion(char **str, int loc, t_data *data)
{
	if ((*str)[loc] == '$' || (*str)[loc] == '~'
		|| (*str)[loc] == '\'' || (*str)[loc] == '\"')
	{
		if ((*str)[loc] == '~' && loc == 0
			&& ((*str)[loc + 1] == '\0' || (*str)[loc + 1] == '/'))
			loc = home_value(str, loc, data->envplist);
		else if ((*str)[loc] == '$')
			loc = replace_dollar(str, loc, data);
		else if ((*str)[loc] == '\"')
			loc = expand_double_quote(str, loc, data);
		else if ((*str)[loc] == '\'')
			loc = replace_quotes1(str, loc, '\'');
	}
	return (loc);
}

char	**expansion(char **str, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if (str[i][j] == '$' || str[i][j] == '~'
				|| str[i][j] == '\'' || str[i][j] == '\"')
				j = if_expansion(&str[i], j, data);
			j++;
		}
		i++;
	}
	return (str);
}
