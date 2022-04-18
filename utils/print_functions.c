#include "../includes/minishell.h"

void	print_envp(char **envp)
{
	int i;
	 i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void print_token(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i] != NULL)
	{
		printf("[%d]: %s,", i, tokens[i]);
		i++;
	}
	printf("\n");
}

void print_cmd_blocks(t_list *cmd_blocks)
{
	t_list	*temp_block;
	t_red	*temp_redirect;
	int		i;

	temp_block = cmd_blocks;
	while (temp_block != NULL)
	{
		printf("index: %d\n", temp_block->index_cmd);
		if (temp_block->cmd != NULL)
		{
			i = 0;
			while (temp_block->cmd[i] != NULL)
			{
				printf("cmd[%d]: %s ", i, temp_block->cmd[i]);
				i++;
			}
			printf("\n");
		}
		temp_redirect = temp_block->redirect;
		if (temp_redirect != NULL)
		{
			while (temp_redirect != NULL)
			{
				printf("op: %s\n", (temp_block->redirect)->op);
				printf("file: %s\n",(temp_block->redirect)->file);
				temp_redirect = temp_redirect->next;
			}
			printf("\n");
		}
		printf("\n");
		temp_block = temp_block->next;
	}
}
