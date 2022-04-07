#include <stdlib.h>
#include <stdio.h>
//getenv function apparently will get the value of the env variable 
//in minishell we get a copy of it and thus have no use for it.
int main()
{
	char *s = getenv("TEST");
	if (s != NULL)
		printf("%s\n",s);
	else
		printf("no TEST");
	return(0);
}

