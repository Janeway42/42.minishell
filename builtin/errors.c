#include "builtin.h"

void	malloc_error_exit(void)
{
	printf("Malloc error.\n");
	exit(1);
}
