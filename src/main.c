#include "../includes/minishell.h"

void	set_up_shell_terminal(t_data *data)
{
	if (isatty(0) == 0)
		exit_on_error("Error: ", 1);
	if (tcgetattr(0, &data->term_with_echo) == -1) //old
		exit_on_error("Exit: ", 1);
	data->term_without_echo = data->term_with_echo;
	data->term_without_echo.c_lflag &= ~(ECHOCTL); /* local mac flag - removes echoctl */
//	data->term_without_echo.c_lflag &= ~(0001000);  /*-  linux flag */
	if (tcsetattr(0, TCSANOW, &data->term_without_echo) == -1)
		exit_on_error("Error: ", 1);
}

/*
** SIGINT The process was “interrupted” (CTRL + C)
** SIGQUIT issued if the user sends a quit signal (CTRL + D)
** SIG_IGN macro defining a signal startegie for signal() = signal is ignored
*/

static void	initialize_minishell(int argc, char **argv, char **envp, t_data *data)
{
	char	*number;
	int		level;
	char	*shelllevel;

	(void)argc;
	(void)argv;

	data->envplist = copy_envp(envp);
	data->inpipe_fd = -1;
	data->outpipe_fds[1] = -1;
	set_variable(&data->envplist,"OLDPWD=");
	set_variable(&data->envplist, "?=0");
	set_variable(&data->envplist,"A=hello"); // variable for testing -> remove once testing is complete 
	set_variable(&data->envplist,"B=bye"); // variable for testing -> remove once testing is complete 
	set_up_shell_terminal(data);
	data->last_exit_code = 0;
	
	number = get_var_value(data->envplist, "SHLVL");
	level = ft_atoi(number);
	free(number);
	level++;
	number = ft_itoa(level);
	if (number == NULL)
		exit_on_error("Error :", 1);
	shelllevel = ft_strjoin("SHLVL=", number);
	if (shelllevel == NULL)
		exit_on_error("Error :", 1);
	free(number);
	set_variable(&(data->envplist), shelllevel);
	free(shelllevel);

}

void	set_exit_code(t_data *data)
{
	char *number;
	char *question_var;

	number = ft_itoa(data->last_exit_code);
	if (number == NULL)
		exit_on_error("Error :", 1);
	question_var = ft_strjoin("?=", number);
	if (question_var == NULL)
		exit_on_error("Error :", 1);
	free(number);
	printf("current value question var: %s\n",question_var);
	set_variable(&data->envplist, question_var);
	free(question_var);
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	*data;
	t_list	*cmd_blocks;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (-1); // check what type of error it needs to return
	initialize_minishell(argc, argv, envp, data);
	while (1)
	{
		signal(SIGINT, sig_handler); // if SIGINT is received then do sig_handler
		signal(SIGQUIT, SIG_IGN);
		if (tcsetattr(0, TCSANOW, &data->term_without_echo) == -1) // set terminal to not allow echoctl 
			exit_on_error("Error: ", 1);
		line = readline(PROMPT);
//		line = "echo \"-n -n -n\"-n bonjour";
//		line = "echo \"\"\"\"$USER\"\"\"\"";
//		line = "echo \"text\" \"text$USER\" ... \"$USER\"";
		if (tcsetattr(0, TCSANOW, &data->term_with_echo) == -1) // set terminal to allow echoctl 
			exit_on_error("Error: ", 1);
		signal(SIGINT, SIG_IGN);
		data->last_exit_code = 0;
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
			{
				data->heredoc_index_array = create_heredoc_index_array(cmd_blocks);
				if (data->heredoc_index_array != NULL)
					data->last_exit_code = process_heredoc(cmd_blocks);
				if (data->last_exit_code == 0)
					process_commands(cmd_blocks, data);
			}
			free_cmd_blocks(&cmd_blocks);
		}
		set_exit_code(data);
		if (data->heredoc_index_array != NULL)
			clean_heredoc_temp_files();
		free(line);
	}
	rl_clear_history();
	free_data(&data);
	return (0);
}

//		line = ">outputfile";
//		line = "echo \"$?TEST\"";
//		line = "\"\"|ls";
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
