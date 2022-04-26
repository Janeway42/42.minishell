#include "../includes/minishell.h"

char *clean_extra_quotes(char *str)
{
	int open_d;
	int open_s;
	int i;

	i = 0;
	open_d = 0;
	open_s = 0;

	while (str[i] != '\0')
	{
		if (str[i] == 39 || str[i] == 34)
		{
			if (str[i] == 39)
			{
				if (open_s == 0 && open_d == 0)
				{
					open_s = 1;
					if (str[i + 1] == 39 && open_s == 1)
					{
						str = replace_quotes(str, i, 39);
						open_s = 0;
						i = i - 1;
					}
				}
				else if (open_s == 1 && open_d == 0)
					open_d = 0;
			}
			else if (str[i] == 34)
			{
				if (open_d == 0 && open_s == 0)
				{
					open_d = 1;
					if (str[i + 1] == 34 && open_d == 1)
					{
						str = replace_quotes(str, i, 34);
						open_d = 0;
						i = i - 1;
					}
				}
				else if (open_d == 1 && open_s == 0)
					open_d = 0;
			}
		}
		i++;
	}
	return (str);
}

//--------------------------------------------

static int	check_unclosed_quotes(char *str)
{
	int	i;
	int	one;
	int	two;

	i = 0;
	one = 0;
	two = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39)
		{
			if (one == 0)
				one = 1;
			else if (one == 1)
				one = 0;
		}
		if (str[i] == 34)
		{
			if (two == 0)
				two = 1;
			else if (two == 1)
				two = 0;
		}
		i++;
	}
	if (one == 1 || two == 1)
		return (1);
	return (0);
}

//-------------------------------------------------

static int just_spaces(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 32)
			return (1);
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

t_list	*parse_line(char *str, t_data *data)
{
	char	**tokens;
	t_list	*cmd_blocks;

	if (just_spaces(str) == 0)
		return (NULL);
	if (check_unclosed_quotes(str) == 1)
		printf("syntax error: unclosed quotes\n");
	else
	{
		str = clean_extra_quotes(str);
		tokens = ft_split_minishell(str, ' ');
		print_token(tokens);
		if (tokens != NULL)
		{
			if (check_syntax(tokens) == 1)
				error_syntax(tokens);
			else
			{
				tokens = expansion(tokens, data);
				print_token(tokens); // remove once completed !!!!!!!!!
				cmd_blocks = set_cmd_blocks(tokens);
				print_cmd_blocks(cmd_blocks); // remove once completed !!!!!!!!!
				free_string_array(tokens);
				return (cmd_blocks);
			}
		}
	}
	return (NULL);
}
