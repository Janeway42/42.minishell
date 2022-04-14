#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //dup2 , close
#include <fcntl.h> //open
#include <string.h>

#include <readline/readline.h> //readline
#include <readline/history.h> //readline
#include "../includes/libft.h"


// the heredoc will write the input in to an temporary file
// close it when done. Open again when done and use dup2 to overwrite with
// the fd from the opened file.

void ft_heredoc()
{
	int filefd = open("tmp.txt", O_TRUNC |  O_WRONLY | O_CREAT, 0700);
	int done = 0;
	char *s;
	while(!done)
	{
		s = readline(">");
		if (s == NULL || strcmp(s, "END") == 0)
		{
			printf("ending\n");
			done = 1;
			close(filefd);
		}
		else
		{
			write(filefd, s, strlen(s));
			write(filefd,"\n",1);
		}
	}
}
	

int main()
{
	ft_heredoc();
	int filefd = open("tmp.txt", O_RDONLY);
	puts("start");
	dup2(filefd, 0);
	char *args[]= {"/bin/cat", NULL};
	if (execv(args[0], args) == -1)
		puts("problems");
	if (unlink("tmp.txt") == -1)
		puts("problem unlinking");
	return (0);
}
