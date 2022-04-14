#include <unistd.h>
#include <stdio.h>
//this program will get the current work directory and change the workdirectory and then
//show the contents of the directory.
int main()
{
	char *dir = getcwd(NULL,0);
	printf("%s\n", dir);

	int i = chdir("../");

	dir = getcwd(NULL,0);
	printf("%s\n", dir);

	char *argv[]={"/bin/ls","-la",NULL};
	execv(argv[0],argv);

	return(0);
}