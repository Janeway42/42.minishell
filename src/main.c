#include "../includes/minishell.h"

/*
** rl_replace_line("", 0); replaces the cotents of rl_line_buffer with ""
** rl_on_new_line(); tells the update functions we have moved onto a new (empty) line,
** usually after outputting a newline.
** rl_redisplay(); change what's displayed on the screen to reflect
** the current contents of rl_line_buffer.
*/

void sig_handler(int sig_no)
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
	if (isatty(0) == 0)
		exit_on_error("Error: ", 1);
	if (tcgetattr(0, &data->term_with_echo) == -1) //old
		exit_on_error("Exit: ", 1);
	data->term_without_echo = data->term_with_echo;
	data->term_without_echo.c_lflag &= ~(ECHOCTL); /* local mac flag - removes echoctl */
/*	data->new_term.c_lflag &= ~(0001000);  -  linux flag */
	if (tcsetattr(0, TCSANOW, &data->term_without_echo) == -1)
		exit_on_error("Error: ", 1);
}

/*
** SIGINT The process was “interrupted” (CTRL + C)
** SIGQUIT issued if the user sends a quit signal (CTRL + D)
** SIG_IGN macro defining a signal startegie for signal() = signal is ignored
*/

static void	initialize_minishell(int argc, char **argv, char **envp, t_data **data)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, sig_handler); // if SIGINT is received then do sig_handler
	signal(SIGQUIT, SIG_IGN);

	(*data)->envplist = copy_envp(envp);
	(*data)->inpipe_fd = -1;
	(*data)->outpipe_fds[1] = -1;
	set_variable(&(*data)->envplist,"OLDPWD=");
	set_variable(&(*data)->envplist,"A=hello");  // erase once no longer needed
	set_variable(&(*data)->envplist,"B=bye");   // erase once no longer needed
	set_up_shell_terminal(*data);
	(*data)->last_exit_code = 0;
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	*data;
	t_list	*cmd_blocks;

	if (!argc)
		return (1);
	(void)argv;
	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (-1); // check what type of error it needs to return
	initialize_minishell(argc, argv, envp, &data);

	while (1)
	{
		if (tcsetattr(0, TCSANOW, &data->term_without_echo) == -1) // set terminal to not allow echoctl 
			exit_on_error("Error: ", 1);
		line = readline(PROMPT);
//		line = "echo $TEST$TEST=lol$TEST""lol";
		if (tcsetattr(0, TCSANOW, &data->term_with_echo) == -1) // set terminal to allow echoctl 
			exit_on_error("Error: ", 1);
		if (line == NULL) // in case of CTRL + D
		{
			write(2, "exit\n", 5);
			exit(0);
		}
		if (line != NULL && ft_strcmp(line, "") != 0)
		{
			add_history(line);
			cmd_blocks = parse_line(line, data);
			if (cmd_blocks != NULL)
				process_commands(cmd_blocks, data);
			free_cmd_blocks(&cmd_blocks);
		}
		free(line);
	}
//	rl_clear_history();
	free_data(&data);
	return (0);
}

//		line = "echo ana";
//		line = "echo ana  ";
//		line = "12345|12345|12345";
//		line = "< src/main.c grep line | grep l| wc -l";  ///
//		line = "<'input.txt'> $A.txt | ls";
//		line = "<'input.txt'> $A.txt | $B >  ls";
//		line = "<'input.txt'> $A.txt | > $B ls";
//		line = "< src/main.c grep line | >";
//		line = "pwd | echo ana";
//		line = ""
