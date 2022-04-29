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

static int	check_pairs(char *str, char c)
{
	int	i;
	int	pair;

	i = 0;
	pair = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			if (pair == 0)
				pair = 1;
			else if (pair == 1)
				pair = 0;
		}
		i++;
	}
	if (pair == 1)
		return (1);
	return (0);
}

//-------------------------------------------------

char	*clean_extra_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && str[i + 1] != '\'')
			i = run_through_quotes(str, i, '\'');
		else if (str[i] == '\"' && str[i + 1] != '\"')
			i = run_through_quotes(str, i, '\"');
		else if (str[i] == '\'' && str[i + 1] == '\'')
			i = replace_quotes1(&str, i, '\'');
		else if (str[i] == '\"' && str[i + 1] == '\"')
			i = replace_quotes1(&str, i, '\"');
		else
			i++;
	}
	printf("str: %s\n", str);
	return (str);
}

/*
**-------------------------------------------------------------------------
** Function splits the input into individual tokens
** If syntax check and expansion go through, the tokens get placed
** into comand blocks to be used by the execve function
*/

t_list	*parse_line(char *str, t_data *data)
{
	char	**tokens;
	t_list	*cmd_blocks;

	if (just_spaces(str) == 0)
		return (NULL);
	if (check_pairs(str, 39) == 1 || check_pairs(str, 34) == 1)
		printf("syntax error: unclosed quotes\n");
	else
	{
		str = clean_extra_quotes(ft_strdup(str));
		tokens = ft_split_minishell(str, ' ');
		print_token(tokens); // remove once completed !!!!!!!!!
		if (tokens != NULL)
		{
			if (check_syntax(tokens) == 1)
				error_syntax(tokens);
			else
			{
				tokens = expansion(tokens, data);
//				print_token(tokens); // remove once completed !!!!!!!!!
				cmd_blocks = set_cmd_blocks(tokens);
//				print_cmd_blocks(cmd_blocks); // remove once completed !!!!!!!!!
				free_string_array(tokens);
				return (cmd_blocks);
			}
		}
	}
	return (NULL);
}
