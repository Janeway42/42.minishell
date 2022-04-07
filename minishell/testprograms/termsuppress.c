#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*
 COMPILE WITH THE NEW READLINE LIBRARY
 THE OLD READLINE LIBRARY WON'T SUPPRESS THE ECHOCTL
 you can test it with system("stty -a | grep echoctl")
 it will show that echoctl will be enabled when using the old readline
 this will not be the case with the new readline

 also on linux the bit mask for echoctl is a bit different compared to the mac 
 bit mask for echoctl
 you can lookup the bitmask by going to the termios.h and look for the 
 definition of ECHOCTL
*/

void sig_handler(int sig_no)
{
	rl_replace_line("",0); //set the rl_buffer to ""
	write(1,"\n",1); //write a new line
	rl_on_new_line();//tell readline that it is on a newline
	rl_redisplay();//display the buffer which is empty now
}
 
int main()
{
	char *input;
	
	struct termios old_term;
	struct termios new_term;

	tcgetattr(0, &old_term);
	new_term = old_term;

//	new_term.c_lflag &= ~(0001000); //linux
printf("%lx\n",new_term.c_lflag);
	new_term.c_lflag &= ~(ECHOCTL); 
printf("%lx\n",new_term.c_lflag);

	//tcsetattr(0, TCSANOW, &new_term);
	
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		input = readline("test>");
		if(input == NULL)
			exit(0);
		if(input[0] =='o')
		{
			tcsetattr(0, TCSANOW, &old_term);
		}	
		else if(input[0] == 'n')
		{
			tcsetattr(0, TCSANOW, &new_term);
		}
		free(input);
	}
}
