#include "../includes/minishell.h"

t_list	*parse_line(char *str, t_data *data)
{
	char	**tokens;
	t_list	*cmd_blocks;

	tokens = ft_split_minishell(str, ' ');
	if (tokens != NULL)
	{
		if (check_syntax(tokens) == 1)
			error_syntax(&tokens);
		else 
		{
			tokens = expansion(tokens, data);
			print_token(tokens);  // remove once completed
			cmd_blocks = set_cmd_blocks(tokens);
			free_double(&tokens);
//			print_cmd_blocks(cmd_blocks);
			return (cmd_blocks);
		}
	}
	return (NULL);
}
