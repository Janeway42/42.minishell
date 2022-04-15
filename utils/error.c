#include "../includes/minishell.h"

void	error_syntax(char ***tokens)
{
	printf("error syntax\n");
	free_double(tokens);
}

void	malloc_error_exit(void) // duplicate function 
{
	printf("Malloc error.\n");
	exit(1);
}

void	exit_on_error(char *message, int exit_code)
{
	perror(message);
	exit(exit_code);
}
