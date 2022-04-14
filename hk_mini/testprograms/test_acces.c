#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	char *paths[]={
		"/usr/bin/ls",
		"usr/bin/./ls",
		"usr/bin/../ls",
		"ls",
		"./ls",
		"../ls",
		NULL
	}
	int i = 0;
	while (paths[i] != NULL)
	printf("%d\n",access("/usr/bin/ls", F_OK));
	printf("%d\n",access("/usr/bin/./ls", F_OK));
	printf("%d\n",access("/usr/bin/../ls", F_OK));
	printf("%d\n",access("ls", F_OK));
	printf("%d\n",access("./ls", F_OK));
	return(0);
}
