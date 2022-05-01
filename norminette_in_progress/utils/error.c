#include "../includes/minishell.h"

void	error_syntax(char **tokens, char ***envplist)
{
	write(2, "error syntax\n", 14);
	free_string_array(tokens);
	set_variable(envplist, "?=258");
}

void	exit_on_error(char *message, int exit_code)
{
	perror(message);
	exit(exit_code);
}
