/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:51:39 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 17:51:42 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//	function that process the heredoc input

void	process_input(int file_fd, char **delim, int i)
{
	int		done;
	char	*input;

	done = FALSE;
	while (done == FALSE)
	{
		input = readline(">");
		if (input == NULL || ft_strcmp(input, delim[i]) == 0)
		{
			done = TRUE;
			close(file_fd);
		}
		else
		{
			write(file_fd, input, ft_strlen(input));
			write(file_fd, "\n", 1);
		}
		free(input);
	}
}

//	function that counts the amount of heredoc in the redirect linked list
int	count_heredoc_in_redirect(t_red *redir)
{
	int	count;

	count = 0;
	while (redir != NULL)
	{
		if (ft_strcmp("<<", redir->op) == 0)
			count++;
		redir = redir->next;
	}
	return (count);
}

//	function that will create the temporary file for each heredoc
//	the naming convention will be 0.tmp. 1.tmp, 2.tmp, etc.

void	create_temp_files(t_list *cmd_block)
{
	int		i;
	char	*filename;
	int		file_fd;
	char	**delim;

	i = 0;
	delim = get_heredoc_delim(cmd_block);
	while (delim[i] != NULL)
	{
		filename = create_temp_file_name(i);
		file_fd = open(filename, O_TRUNC | O_WRONLY | O_CREAT, 0600);
		free(filename);
		if (file_fd == -1)
			exit_on_error("Error :", 1);
		process_input(file_fd, delim, i);
		i++;
	}
	free_string_array(delim);
	exit(0);
}

//	funtion to create the heredoc temp files 
//	RETURN	the exit code of the heredoc. 
//			it should be 0 if succesfull 

int	process_heredoc(t_list *cmd_block)
{
	pid_t	pid;
	int		wstatus;
	int		last_exit_code;

	last_exit_code = 0;
	pid = fork();
	if (pid < 0)
		exit_on_error("Error :", 1);
	else if (pid == 0)
	{
		signal(SIGINT, heredoc_sighandler);
		signal(SIGQUIT, SIG_IGN);
		create_temp_files(cmd_block);
	}
	else
	{
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			last_exit_code = WEXITSTATUS(wstatus);
	}
	return (last_exit_code);
}

//	function that create an int array containing the starting number of the temp
//	file for each command that has at least one heredoc. if the commmand don't 
//	have a heredoc the int would be -1. if it does have a heredoc it could be 
//	for example be 3. The temporary file would be called 3.tmp

int	*create_heredoc_index_array(t_list *cmd_block)
{
	int		count;
	int		temp_index;
	int		*heredoc_index_array;
	t_red	*redir;

	count = count_commands(cmd_block);
	heredoc_index_array = malloc(sizeof(int) * count);
	if (heredoc_index_array == NULL)
		exit_on_error("Error :", 1);
	temp_index = 0;
	while (cmd_block != NULL)
	{
		redir = cmd_block->redirect;
		count = count_heredoc_in_redirect(redir);
		if (count != 0)
			heredoc_index_array[cmd_block->index_cmd - 1] = temp_index;
		temp_index += count;
		cmd_block = cmd_block->next;
	}
	if (temp_index == 0)
	{
		free(heredoc_index_array);
		return (NULL);
	}
	return (heredoc_index_array);
}
