#include "minishell.h"

void	exit_on_error(char *message, int exit_code)
{
	perror(message);
	exit(exit_code);
}
