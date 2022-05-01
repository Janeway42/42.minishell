/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:39:41 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 17:42:09 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//	function to read the input from read line and return it

static char	*read_input(t_data *data)
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

static void	process_input_line(char *line, t_data *data)
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
