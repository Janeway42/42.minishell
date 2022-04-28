#include "../includes/minishell.h"

char *clean_extra_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && str[i + 1] != '\'')
			i = run_through_quotes(str, i, '\'');
		else if (str[i] == '\"'&& str[i + 1] != '\"')
			i = run_through_quotes(str, i, '\"');
		else if (str[i] == '\'' && str[i + 1] == '\'')
			str = replace_quotes(str, i, '\'');
		else if (str[i] == '\"'&& str[i + 1] == '\"')
			str = replace_quotes(str, i, '\"');
		else
			i++;
	}
	return (str);
}

// char	*clean_extra_quotes(char *str)
// {
// 	int	open_d;
// 	int	open_s;
// 	int	i;

// 	i = 0;
// 	open_d = 0;
// 	open_s = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == 39 || str[i] == 34)
// 		{
// 			if (str[i] == 39)
// 			{
// 				if (open_s == 0 && open_d == 0)
// 				{
// 					open_s = 1;
// 					if (str[i + 1] == 39 && open_s == 1)
// 					{
// 						str = replace_quotes(str, i, 39);
// 						open_s = 0;
// 						i--;
// 					}
// 				}
// 				else if (open_s == 1 && open_d == 0)
// 					open_s = 0;
// 			}
// 			else if (str[i] == 34)
// 			{
// 				if (open_d == 0 && open_s == 0)
// 				{
// 					open_d = 1;
// 					if (str[i + 1] == 34 && open_d == 1)
// 					{
// 						str = replace_quotes(str, i, 34);
// 						open_d = 0;
// 						i--;
// 					}
// 				}
// 				else if (open_d == 1 && open_s == 0)
// 					open_d = 0;
// 			}
// 		}
// 		i++;
// 	}
// 	return (str);
// }

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

/*
**-------------------------------------------------------------------------
** Function splits the input into individual tokens
** If syntax check and expansion go through, the tokens get placed
** into comand blocks to be used by the execve function
*/

t_list	*parse_line(char *str, t_data *data)
{
	char	**tokens;
//	char	*temp;
	t_list	*cmd_blocks;

	if (just_spaces(str) == 0)
		return (NULL);
	if (check_pairs(str, 39) == 1 || check_pairs(str, 34) == 1)
		printf("syntax error: unclosed quotes\n");
	else
	{
//		temp = clean_extra_quotes(ft_strdup(str));   // it needs this on linux - check mac 
		tokens = ft_split_minishell(str, ' ');
//		print_token(tokens); // remove once completed !!!!!!!!!
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
