#include "../includes/minishell.h"

void	free_double(char ***str)
{
	char	**temp;

	temp = *str;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(*str);
}

void	error_syntax(char ***str)
{
	free_double(str);
	printf("error syntax\n");
}

void	malloc_error_exit(void)  // duplicate function 
{
	printf("Malloc error.\n");
	exit(1);
}

void	free_string_array(char **array)  // duplicate function 
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