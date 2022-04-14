#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

//this function is to test how to do the new prompt when CTRL-C is pressed
//(SIGINT).
//This should work correctly now.
//CTRL-C will start a new prompt and not 
//CTRL-\ will be ignored
//CTRL-D will generated the EOF like normal

void sig_handler(int sig_no)
{
	rl_replace_line("",0); //set the rl_buffer to ""
	write(1,"\n",1); //write a new line
	rl_on_new_line();//tell readline that it is on a newline
	rl_redisplay();//display the buffer which is empty now
}

int main()
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	int done = 0;
	char *input;

	while(!done)
	{
		input = readline("testshell>");
		if(input == NULL)
		{
			done = 1;
			continue;
		}
		printf("input is %s\n",input);
		add_history(input);
		free(input);
	}
	return (0);
}
