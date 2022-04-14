#include "minishell.h"
/* 
//testing function
t_cmd_block *create_cmd_block()
{
	t_cmd_block *first= malloc(sizeof (t_cmd_block));
	char *cmd_first[]={"ls","-la",NULL};
	first->cmd_args = cmd_first;
	first->inputfd = 0;
	first->outputfd = 1;
	first->redirs = NULL;
	first->cmdnbr = 1;
	return (first);
}
*/

void	sig_handler(int sig_no)
{
	if (sig_no == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_up_shell_terminal(t_data *data)
{
	if (!isatty(0))
		exit_on_error("Error :", 1);
	else
	{
		if (tcgetattr(0, &(data->old_term)) == -1)
			exit_on_error("Error :", 1);
		data->new_term = data->old_term;
		data->new_term.c_lflag &= ~(ECHOCTL);
		if (tcsetattr(0, TCSANOW, &(data->new_term)) == -1)
			exit_on_error("Error :", 1);
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_cmd_block	*cmd_list;
	char		*input;

(void) argc;
(void) argv;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	data.last_exit_code = 0;
	//data.envp_list = copy_envp(envp);
	set_up_shell_terminal(&data);
	
	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL)
		{
			//maybe free all the things
			printf("exit");
			exit(0);
		}
		if (input[0] != '\0')
			add_history(input);
		//process the input into command blocks
		free(input);
	}
}