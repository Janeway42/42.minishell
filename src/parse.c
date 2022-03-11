#include "../includes/minishell.h"

void parse_line(char *str, t_env *envplist)
{
	int		i;
	char	**tokens;
//	t_list	*cmd_blocks;

	i = 0;
	tokens = ft_split_minishell(str, ' ');
//	if (!tokens)
//		return (NULL);

	while (tokens[i] != '\0')
	{
		printf("%s\n", tokens[i]);
		i++;
	}

	if (check_syntax(tokens) == 1)
		error_syntax(&tokens);
	else
	{
		printf("syntax correct\n");
//		free_double(&tokens);
	}

	tokens = expansion(tokens, envplist);

	i = 0;
	while (tokens[i] != '\0')
	{
		printf("%s - ", tokens[i]);
		i++;
	}
	printf("\n");

	free_double(&tokens);
	

	// set up linked lists 


//	return (cmd_blocks);
}