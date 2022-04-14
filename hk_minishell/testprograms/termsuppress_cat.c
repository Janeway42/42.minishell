#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void handler(int sig)
{
	if (sig == SIGINT)
		printf("test>");
} 

void handler2(int sig)
{
	if (sig == SIGINT)
		printf("shell>");
}

int main()
{
	char *input;
	
	struct termios old_term;
	struct termios new_term;

	tcgetattr(0,&old_term);
	new_term = old_term;

	new_term.c_lflag &= ~(0001000);
	tcsetattr(0, TCSANOW, &new_term);
	
//	signal(SIGINT, handler);
//	signal(SIGQUIT, SIG_IGN);

	char *args[]= {"/bin/cat", NULL};
	if (execv(args[0], args) == -1)
		puts("problems");
	return (0);
}
