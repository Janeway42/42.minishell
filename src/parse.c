#include "../includes/minishell.h"

void print_token(char **tokens) // erase when no longer needed
{
	int i;

	i = 0;
	while (tokens[i] != '\0')
	{
		printf("%s, ", tokens[i]);
		i++;
	}
	printf("\n");
}

void print_cmd_blocks(t_list *cmd_blocks) // erase when no longer needed
{
	t_list	*temp_block;
	t_red	*temp_redirect;

	temp_block = cmd_blocks;
	while (temp_block != NULL)
	{
		printf("index: %d\n", temp_block->index_cmd);
		printf("cmd: ");
		print_token(temp_block->cmd);

		temp_redirect = temp_block->redirect;
		printf("op & file: ");
		while (temp_redirect != NULL)
		{
			printf("%s %s, ", temp_redirect->op, temp_redirect->file);
			temp_redirect = temp_redirect->next;
		}
		printf("\n");
		temp_block = temp_block->next;
	}
}

void parse_line(char *str, t_data *data)
{
	int		i;
	char	**tokens;
	t_list	*cmd_blocks;

	tokens = ft_split_minishell(str, ' ');

//	print_token(tokens); // remove 

	if (check_syntax(tokens) == 1)
		error_syntax(&tokens);
	else // remove once testing is no longer required
	{
		printf("syntax correct\n");
//		free_double(&tokens);
	}

	tokens = expansion(tokens, data->envplist);
	print_token(tokens);  // remove

	cmd_blocks = set_cmd_blocks(tokens, data->envplist);
	free_double(&tokens);

	print_cmd_blocks(cmd_blocks);

//	return (cmd_blocks);
}