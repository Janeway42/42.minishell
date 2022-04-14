#include "minishell.h"


//testing function
t_cmd_block *create_cmd_block()
{
	t_cmd_block *first= malloc(sizeof (t_cmd_block));
	t_cmd_block *second = malloc(sizeof (t_cmd_block));
	t_cmd_block *third = malloc(sizeof (t_cmd_block));
//	t_cmd_block *fourth = malloc(sizeof (t_cmd_block));
//	t_cmd_block *five = malloc(sizeof (t_cmd_block));
	first->next = second;
	second->next = third;
	third->next = NULL;
//	fourth->next = five;
//	five->next = NULL;
	return (first);
}

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
//		data->new_term.c_lflag &= ~(0001000); //linux flag
		data->new_term.c_lflag &= ~(ECHOCTL); //mac flag
		if (tcsetattr(0, TCSANOW, &(data->new_term)) == -1)
			exit_on_error("Error :", 1);
	}
}

void	init_minishell(int argc, char **argv, char **envp, t_data *data)
{
	(void) argc;
	(void) argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	data->envp_list = copy_envp(envp);
	data->inpipe_fd = -1;
	data->outpipe_fds[1] = -1;
	set_variable(&(data->envp_list),"OLDPWD=");
	set_up_shell_terminal(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_cmd_block	*cmd_list;
//	char		*input;

	init_minishell(argc, argv, envp, &data);	
	cmd_list = create_cmd_block();


//---------------------------------------------------
// test
//create test command block
//commands
char *first_cmds[]={"cat",NULL};
char *scnd_cmds[]={"cat",NULL};
char *third_cmds[]={"wc",NULL};
//char *fourth_cmds[]={"cat",NULL};
//char *fifth_cmds[]={"ls",NULL};

//redirections
t_red redir;
t_red redir2;

redir.file = "output.txt";
redir.op = ">";
redir.next = &redir2;

redir2.file = "output2.txt";
redir.op = ">";
redir2.next = NULL;



cmd_list->cmd_args = first_cmds;
cmd_list->redirs = NULL;

cmd_list->next->cmd_args = scnd_cmds;
cmd_list->next->redirs = NULL;

cmd_list->next->next->cmd_args = third_cmds;
cmd_list->next->next->redirs = &redir;

//cmd_list->next->next->cmd_args = third_cmds;
//cmd_list->next->next->next->cmd_args = fourth_cmds;
//cmd_list->next->next->next->next->cmd_args = fifth_cmds;

		//don't forget to free the cmd_list
//---------------------------------------------------


/*
	while (1)
	{
		if (tcsetattr(0, TCSANOW, &(data.new_term)) == -1) //reset the terminal to allow echoctl
			exit_on_error("Error :", 1);
		input = readline(PROMPT);
		if (tcsetattr(0, TCSANOW, &(data.old_term)) == -1) //reset the terminal to allow echoctl
			exit_on_error("Error :", 1);
		if (input == NULL)
		{
			//maybe free all the things
			write(2, "exit\n", 5);
			exit(0);
		}
		if (input[0] != '\0')
			add_history(input);
		process_cmds(cmd_list, &data);
		free(input);
//set the exit code in environment variable `?` to the exitcode
	}
*/
	process_cmds(cmd_list, &data);
	return (0);
}
