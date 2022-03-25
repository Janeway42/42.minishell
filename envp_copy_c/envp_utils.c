#include "../includes/minishell.h"

//	function will copy the given envp list and insert the variable at the end
//	of the list. And it will free the envp list and return the new list
//	RETURN	malloced envp list
void	insert_variable(char ***envp, char *variable)
{
	int		i;
	int		count;
	char	**new_envp;

	count = count_variables(*envp);
	new_envp = malloc (sizeof (char *) * (count + 2));
	if (new_envp == NULL)
		malloc_error_exit();
	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		if (new_envp[i] == NULL)
			malloc_error_exit();
		i++;
	}
	new_envp[count] = ft_strdup(variable);
	if (new_envp[count] == NULL)
		malloc_error_exit();
	new_envp[count + 1] = NULL;
	free_string_array(*envp);
	*envp = new_envp;
}

//	function to set a variable to a certain value
//	RETURN	the list with the value changed or variable 
//			has been added to the list if it wasn't on the list
void	set_variable(char ***envp, char *variable)
{
	int		pos;
	char	**var_split;

	var_split = ft_split_variable(variable);
	pos = find_variable_position(*envp, var_split[0]);
	if (pos != -1)
	{
		free((*envp)[pos]);
		(*envp)[pos] = ft_strdup(variable);
		if ((*envp)[pos] == NULL)
			malloc_error_exit();
	}
	else
		insert_variable(envp, variable);
	free_string_array(var_split);
}

//	support function of function delete_variable()
static void	remove_variable(char ***envp, int position)
{
	char	**new_envp;
	int		count;
	int		i;
	int		j;

	count = count_variables(*envp);
	new_envp = malloc(sizeof(char *) * count);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (i != position)
		{
			new_envp[j] = ft_strdup((*envp)[i]);
			if (new_envp[j] == NULL)
				malloc_error_exit();
			j++;
		}
		i++;
	}
	new_envp[count -1] = NULL;
	free_string_array(*envp);
	*envp = new_envp;
}

//	function will delete the variable from the list if found
//	else it will not do anything.
//	RETURN	the list without the variable
void	delete_variable(char ***envp, char *variable)
{
	int		pos;

	pos = find_variable_position(*envp, variable);
	if (pos != -1)
	{	
		remove_variable(envp, pos);
	}
}

//	function to get the value of the variable in the envp list
//	RETURN	NULL if the variable has no value or is not in the list
//			If found, a malloc string with the value of the variable is returned
char	*get_var_value(char **envp, char *variable)
{
	int		pos;
	char	**split;
	char	*value;

	pos = find_variable_position(envp, variable);
	if (pos != -1)
	{
		split = ft_split_variable(envp[pos]);
		value = split[1];
		free(split[0]);
		free(split);
		return (value);
	}
	return (NULL);
}

/*
//test
void print_list(char **list)
{
	for(int i = 0; list[i] != NULL; i++)
		printf("%s\n", list[i]);
}

//test
int main(int argc, char **argv, char **envp)
{	
	char **envp_copy = copy_envp(envp);
	insert_variable(&envp_copy,"a");
	puts("----------------------------------------");
	print_list(envp_copy);
	puts("----------------------------------------");
	set_variable(&envp_copy,"b");
	set_variable(&envp_copy, "a=\"123\"");
	print_list(envp_copy);
	puts("----------------------------------------");
	delete_variable(&envp_copy, "b");
	delete_variable(&envp_copy, "a");
	delete_variable(&envp_copy, "SHELL");
	delete_variable(&envp_copy, "LOG");
	print_list(envp_copy);
	puts("----------------------------------------");
	char *value = get_var_value(envp_copy,"a");
	printf("value %s\n",value);
	free(value);
	free_string_array(envp_copy);
	while(1);
	return (0);
}
*/