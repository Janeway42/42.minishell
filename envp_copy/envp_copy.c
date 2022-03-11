#include "../includes/minishell.h"

//	will try the find the position of the char c in the given string 
//	RETURN	ith position in the string if found
//			-1 if it has not found the char c
static int	find_char_pos(char *s, char c)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}

//	will split the environment variable into key and value
//	if it has not value only the key will be returned.
char	**ft_split_env(char *env)
{
	int		i;
	char	**split;

	i = find_char_pos(env, '=');
	if (i == -1)
	{
		split = malloc(sizeof (char *) * 2);
		if (split == NULL)
			printf("malloc error"); //malloc exit error
		split[0] = ft_strdup(env);
		split[1] = NULL;
	}
	else
	{
		split = malloc(sizeof (char *) * 3);
		if (split == NULL)
			printf("malloc error"); //malloc exit error
		split[0] = ft_substr(env, 0, i);
		split[1] = ft_strdup(&env[i + 1]);
		split[2] = NULL;
	}
	return (split);
}

//	create a node with the given key and value
t_env	*create_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof (t_env));
	if (node == NULL)
		printf("Malloc error"); //error exit
	node->key = key;
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

//	function to be used to free the created linked list of envp
void	free_envp_list(t_env *list)
{
	t_env	*current;
	t_env	*temp;

	current = list;
	while (current != NULL)
	{
		temp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = temp;
	}
}

//	function that will create a copy of the envp list and return
//	it in the format of a sorted linked list
t_env	*envp_copy(char **envp)
{
	t_env	*list;
	char	**split;
	int		i;

	i = 0;
	list = NULL;
	while (envp[i] != NULL)
	{
		split = ft_split_env(envp[i]);
		insert_node_sorted(&list, create_node(split[0], split[1]));
		free(split);
		i++;
	}
	return (list);
}


// void	print_envp(t_env *list)
// {
// 	t_env	*current = list;

// 	while (current != NULL)
// 	{
// 		printf("%s=%s\n", current->key, current->value);
// 		current = current->next;
// 	}
// 	printf("\n");
// }

// //TEST
// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*envplist = envp_copy(envp);

// 	print_envp(envplist);
// 	set_env(&envplist,"A","hello");
// 	print_envp(envplist);
// 	del_env(&envplist,"A");
// 	print_envp(envplist);
// 	return (0);
// }
