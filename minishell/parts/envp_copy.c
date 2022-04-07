#include "minishell.h"

//	function to free all the strings and the array itself.
void	free_string_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	count_variables(char **array)
{
	int	count;

	count = 0;
	while (array[count] != NULL)
		count++;
	return (count);
}

//	function will attempt to find the variable and return the position in the
//	envp list.
int	find_variable_position(char **envp, char *variable)
{
	int		i;
	char	**split;

	i = 0;
	while (envp[i] != NULL)
	{
		split = ft_split_variable(envp[i]);
		if (ft_strcmp(variable, split[0]) == 0)
		{
			free_string_array(split);
			return (i);
		}
		free_string_array(split);
		i++;
	}
	return (-1);
}

//	will split the environment variable into key and value
//	if it has not value only the key will be returned.
char	**ft_split_variable(char *variable)
{
	int		i;
	char	**split;

	split = malloc(sizeof (char *) * 3);
	if (split == NULL)
		exit_on_error("Error :", 1);	
	i = 0;
	split[1] = NULL;
	while (variable[i] != '=' && variable[i] != '\0')
		i++;
	split[0] = ft_substr(variable, 0, i);
	if (split[0] == NULL)
		exit_on_error("Error :", 1);	
	if (variable[i] == '=')
	{
		split[1] = ft_strdup(&variable[i + 1]);
		if (split[1] == NULL)
			exit_on_error("Error :", 1);	
	}
	split[2] = NULL;
	return (split);
}

//	function will create a malloced copy of the envp
char	**copy_envp(char **envp)
{
	int		count;
	char	**envp_copy;
	int		i;

	count = count_variables(envp);
	envp_copy = malloc(sizeof (char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (envp_copy[i] == NULL)
			exit_on_error("Error :", 1);	
		i++;
	}
	envp_copy[count] = NULL;
	return (envp_copy);
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
	envp_copy = insert_variable(envp_copy, "hello=1");
	print_list(envp_copy);
	free_string_array(envp_copy);
	return (0);
}
*/
