#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#define PROMPT "minishell>"

void handle_sig(int signo)
{
	if (signo == SIGINT)
	{
		puts("abort\n");
//		rl_clear_history();
	}
	else if (signo == SIGQUIT)
	{
		printf("quit");
	}
}

int main()
{
	char *s;

	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);

	while(1)
	{
		s = readline(PROMPT);
		if (s == NULL)
		{
			printf("NULL output");
			exit(0);
		}
		else if (*s == '\0')
			printf("no input\n");
		else
			printf("%s\n",s);
		add_history(s);
		free(s);
	}
	return (0);
}
