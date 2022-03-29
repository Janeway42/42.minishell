#include "../includes/minishell.h"

// static t_red	*add_red_elem(char *str1, char *str2, t_red **lst)
// {
// 	t_red *new_elem;
// 	t_red *temp;

// 	new_elem = malloc(sizeof(t_red) * 1);
// 	if (!new_elem)
// 		return (NULL);
// 	new_elem->op = ft_strdup(str1);
// 	new_elem->file = ft_strdup(str2);
// 	new_elem->next = NULL;
	

// 	if (!*lst)
// 		*lst = new_elem;
// 	else
// 	{
// 		temp = *lst;
// 		while (temp != NULL)
// 			temp = temp->next;
// 		temp->next = new_elem;
// 	}
// 	return ()
// }

t_list	*ft_last_block(t_list *x)
{
	t_list	*last;

	if (!x)
		return (NULL);
	last = x;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	create_add_new_block(t_list **cmd_blocks, int index)
{
	t_list *new_elem;
	t_list *temp;

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

void add_to_redirect(t_red **lst, char *str1, char *str2)
{
	t_red *new_elem;
	t_red *temp;

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

int	size_double_array(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

void	create_cmd(char ***cmd, char *token)
{
	*cmd = malloc(sizeof(char *) * 2);
	if (!*cmd)
		malloc_error_exit();
	(*cmd)[0] = ft_strdup(token);
	(*cmd)[1] = NULL;
}

void	join_arrays(char ***cmd, char *token)  // duplicate function insert_variable(char ***envp, char *variable)
{
	int	i;
	int	size;
	char **new_block;

	i = 0;
	size = size_double_array(*cmd);
	new_block = malloc(sizeof(char *) * (size + 2));
	if (!new_block)
		malloc_error_exit();
	new_block[size + 1] = NULL;
	while (i < size)
	{
		new_block[i] = ft_strdup(*cmd[i]);
		if (!new_block[i])
			malloc_error_exit();
		i++;
	}
	new_block[size] = ft_strdup(token);
	if (!new_block[size])
		malloc_error_exit();
	free_string_array(*cmd);
	*cmd = new_block;
}

t_list *set_cmd_blocks(char **tokens)
{
	t_list	*cmd_blocks;
	t_list	*temp;
	int		i;
	int		pipes;

	i = 0;
	pipes = 0;
	create_add_new_block(&cmd_blocks, pipes);
//	print_cmd_blocks(cmd_blocks);
	temp = cmd_blocks;
	while (tokens[i] != '\0')
	{
		while (tokens[i] != '\0' && ft_strcmp(tokens[i], "|") != 0)
		{
			if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], "<<") == 0
				|| ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0 )
				{
					add_to_redirect(&temp->redirect, tokens[i], tokens[i + 1]);
//					printf("op: %s\n", cmd_blocks->redirect->file);
//					printf("file: %s, %d\n", cmd_blocks->redirect->file, i);
					i++;
				}
			else
			{
				if (temp->cmd != NULL)
					join_arrays(&temp->cmd, tokens[i]);
				else
					create_cmd(&temp->cmd, tokens[i]);
			}
			i++;
		}
		pipes++;
		temp->index_cmd = pipes;
		if (tokens[i] == '\0')
			return (cmd_blocks);
		create_add_new_block(&temp, pipes);
		temp = ft_last_block(temp);
		i++;
	}
	return (cmd_blocks);
}