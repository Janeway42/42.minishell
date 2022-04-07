#include <unistd.h>
#include <stdio.h>
//test program to see how chdir works

int main(int argc, char **argv)
{
	char *dir = getcwd(NULL,0);
	printf("%s\n", dir);

	if(chdir(argv[1]))
		perror(argv[1]);
	else 
	{
		char *dir = getcwd(NULL,0);
		printf("%s\n", dir);
	}	

	return(0);
}