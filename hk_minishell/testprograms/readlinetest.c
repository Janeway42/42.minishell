#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char *input;
	int done = 0;

	while(!done)
	{
		input = readline("tst>");
		
		free(input);
	}
}