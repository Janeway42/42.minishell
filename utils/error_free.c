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