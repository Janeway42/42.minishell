#include "../includes/minishell.h"

void	set_shell_level(t_data *data)
{
	char	*number;
	int		level;
	char	*shelllevel;

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

void	set_up_shell_terminal(t_data *data)
{
	if (isatty(0) == 0)
		exit_on_error("Error: ", 1);
	if (tcgetattr(0, &data->term_with_echo) == -1)
		exit_on_error("Exit: ", 1);
	data->term_without_echo = data->term_with_echo;
	data->term_without_echo.c_lflag &= ~(ECHOCTL);
//	data->term_without_echo.c_lflag &= ~(0001000);  /*-  linux flag */
	if (tcsetattr(0, TCSANOW, &data->term_without_echo) == -1)
		exit_on_error("Error: ", 1);
}

/*
** SIGINT The process was “interrupted” (CTRL + C)
** SIGQUIT issued if the user sends a quit signal (CTRL + D)
** SIG_IGN macro defining a signal strategy for signal() = signal is ignored
*/

void	initialize_minishell(int argc, char **argv, char **envp
			, t_data *data)
{
	(void)argc;
	(void)argv;
	data->envplist = copy_envp(envp);
	set_variable(&data->envplist, "OLDPWD=");
	set_variable(&data->envplist, "?=0");
	data->inpipe_fd = -1;
	data->outpipe_fds[1] = -1;
	data->last_exit_code = 0;
	set_up_shell_terminal(data);
	set_shell_level(data);
}

//	will set the exit code to the '?' environment variable.

void	set_exit_code(t_data *data)
{
	char	*number;
	char	*question_var;

	number = ft_itoa(data->last_exit_code);
	if (number == NULL)
		exit_on_error("Error :", 1);
	question_var = ft_strjoin("?=", number);
	if (question_var == NULL)
		exit_on_error("Error :", 1);
	free(number);
	printf("current value question var: %s\n", question_var); //test
	set_variable(&data->envplist, question_var);
	free(question_var);
}

//	function to read the input from read line and return it

char	*read_input(t_data *data)
{
	char	*line;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	if (tcsetattr(0, TCSANOW, &data->term_without_echo) == -1)
		exit_on_error("Error: ", 1);
	line = readline(PROMPT);
	if (tcsetattr(0, TCSANOW, &data->term_with_echo) == -1)
		exit_on_error("Error: ", 1);
	signal(SIGINT, SIG_IGN);
	if (line == NULL)
	{
		write(2, "exit\n", 5);
		exit(0);
	}
	return (line);
}

void	process_input_line(char *line, t_data *data)
{
	t_list	*cmd_blocks;

	if (line != NULL && ft_strcmp(line, "") != 0)
	{
		add_history(line);
		cmd_blocks = parse_line(line, data);
		if (cmd_blocks != NULL)
		{
			data->heredoc_index_array = create_heredoc_index_array(cmd_blocks);
			if (data->heredoc_index_array != NULL)
				data->last_exit_code = process_heredoc(cmd_blocks);
			if (data->heredoc_index_array == NULL)
				process_commands(cmd_blocks, data);
			else if (data->heredoc_index_array != NULL
				&& data->last_exit_code == 0)
				process_commands(cmd_blocks, data);
		}
		free_cmd_blocks(&cmd_blocks);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	*data;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (1);
	initialize_minishell(argc, argv, envp, data);
	while (1)
	{
		line = read_input(data);
		process_input_line(line, data);
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