#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
// changing the directory in the child process will not affect the cwd of the 
// process

int main()
{
	int wstatus;
	int pid = fork();
	if(pid == 0)
	{
		char *dir = getcwd(NULL,0);
		printf("child process dir: %s\n", dir);

		int i = chdir("../");

		dir = getcwd(NULL,0);
		printf("child process dir: %s\n", dir);

		char *argv[]={"/bin/ls","-la",NULL};
		execv(argv[0],argv);

		return(0);
	}
	else if(pid > 0)
	{
		wait(&wstatus); //wait till child is done and then display the cwd
		char *dir = getcwd(NULL,0);
		printf("parent process dir :%s\n", dir);
	}
	return (0);
}