#include "../includes/minishell.h"

void	create_add_new_block(t_list **cmd_blocks, int index)
{
	t_list	*new_elem;
	t_list	*temp;

	new_elem = malloc(sizeof(t_list) * 1);
	if (!new_elem)
		malloc_error_exit();
	new_elem->next = NULL;
	new_elem->redirect = NULL;
	new_elem->cmd = NULL;
	new_elem->index_cmd = index;
	if (*cmd_blocks == NULL)
		*cmd_blocks = new_elem;
	else
	{
		temp = *cmd_blocks;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_elem;
	}
}

void	add_to_redirect(t_red **lst, char *str1, char *str2)
{
	t_red	*new_elem;
	t_red	*temp;

	new_elem = malloc(sizeof(t_red) * 1);
	if (!new_elem)
		malloc_error_exit();
	new_elem->next = NULL;
	new_elem->op = ft_strdup(str1);
	new_elem->file = ft_strdup(str2);
	if (*lst == NULL)
		*lst = new_elem;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_elem;
	}
}

void	create_cmd(char ***cmd, char *token)
{
	*cmd = malloc(sizeof(char *) * 2);
	if (!*cmd)
		malloc_error_exit();
	(*cmd)[0] = ft_strdup(token);
	(*cmd)[1] = NULL;
}

int	add_to_blocks(t_list *list, char **str, int loc)
{
	if (ft_strcmp(str[loc], "<") == 0
		|| ft_strcmp(str[loc], "<<") == 0
		|| ft_strcmp(str[loc], ">") == 0
		|| ft_strcmp(str[loc], ">>") == 0)
	{
		add_to_redirect(&list->redirect, str[loc], str[loc + 1]);
		loc++;
	}
	else
	{
		if (list->cmd != NULL)
			join_arrays(&list->cmd, str[loc]);
		else
			create_cmd(&list->cmd, str[loc]);
	}
	loc++;
	return (loc);
}

/*
**-------------------------------------------------------------------------
**	identify and copy the elements of the input line
**	into the right position in the command blocks that will be
**	used by the execve function in the child processes
*/

t_list	*set_cmd_blocks(char **tokens)
{
	t_list	*cmd_blocks;
	t_list	*temp;
	int		i;
	int		nr_blocks;

	i = 0;
	nr_blocks = 1;
	cmd_blocks = NULL;
	create_add_new_block(&cmd_blocks, nr_blocks);
	temp = cmd_blocks;
	while (tokens[i] != NULL)
	{
		while (tokens[i] != NULL && ft_strcmp(tokens[i], "|") != 0)
			i = add_to_blocks(temp, tokens, i);
		if (tokens[i] == NULL)
			return (cmd_blocks);
		nr_blocks++;
		create_add_new_block(&cmd_blocks, nr_blocks);
		temp = ft_last_block(cmd_blocks);
		i++;
	}
	return (cmd_blocks);
}
