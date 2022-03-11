#include "../includes/minishell.h"

//	insert the node at the back of the list
//	assumes the list is not empty
void	insert_back_of_list(t_env **begin_list, t_env *node)
{
	t_env	*current;

	current = *begin_list;
	while (current->next != NULL)
		current = current->next;
	current->next = node;
	node->prev = current;
}

//	insert the node in the list in a sorted way
void	insert_node_sorted(t_env **begin_list, t_env *node)
{
	t_env	*current;

	if (*begin_list == NULL)
		*begin_list = node;
	else
	{
		current = *begin_list;
		while (current != NULL && ft_strcmp(node->key, current->key) >= 0)
			current = current->next;
		if (current == NULL)
			insert_back_of_list(begin_list, node);
		else if (current->prev == NULL)
		{
			*begin_list = node;
			node->next = current;
			current->prev = node;
		}
		else
		{
			node->prev = current->prev;
			node->next = current;
			node->prev->next = node;
			current->prev = node;
		}
	}
}

//	function that will set the environment variable to the given value
//	if variable is not found it will create a new node and insert it to 
//	the list

void	set_env(t_env **envp_list, char *key, char *value)
{
	t_env	*current;

	current = *envp_list;
	while (current != NULL)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			if (value != NULL)
			{
				free(current->value);
				current->value = value;
			}
		}
		else
			current = current->next;
	}
	if (current == NULL)
	{
		insert_node_sorted(envp_list, create_node(key, value));
	}
}

//	this function will delete the variable if it's key value matches that of the
//	given key. If the variable is not found it won't do anything.
void	del_env(t_env **envp_list, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *envp_list;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			if (prev == NULL)
				*envp_list = current->next;
			else
			{
				prev->next = current->next;
				current->next->prev = prev;
				free(current->key);
				free(current->value);
				free(current);
			}
			break ;
		}
		else
			current = current->next;
	}
}

//	function that will get the value of a environmental variable. If found
//	it will create a malloced copy of the value
//	RETURN	malloced copy of the value of the variable
//			NULL if the variable don't exist or has not been set.

char	*get_env(t_env *envp_list, char *key)
{
	t_env	*current;
	char	*value;

	current = envp_list;
	while (current != NULL)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			value = ft_strdup(current->value);
			return (value);
		}
		current = current->next;
	}
	return (NULL);
}
