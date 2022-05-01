/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:52:02 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 17:52:03 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	Function redirects STDIN to inputfile
*/

int	redir_input(char *filename, int sole_builtin)
{
	int	input_fd;

	input_fd = open(filename, O_RDONLY);
	if (input_fd == -1 && sole_builtin)
		return (1);
	if (input_fd == -1)
		exit_on_error(filename, 1);
	dup2(input_fd, 0);
	close(input_fd);
	return (0);
}

/*
** Function redirects STDOUT to outfile (non-append)
*/

int	redir_output(char *filename, int sole_builtin)
{
	int	output_fd;

	output_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (output_fd == -1 && sole_builtin)
		return (1);
	if (output_fd == -1)
		exit_on_error(filename, 1);
	dup2(output_fd, 1);
	close(output_fd);
	return (0);
}

/*
**	Funcion that redirect STDOUT to outfile (append)
*/

int	redir_output_append(char *filename, int sole_builtin)
{
	int	output_fd;

	output_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0755);
	if (output_fd == -1 && sole_builtin)
		return (1);
	if (output_fd == -1)
		exit_on_error(filename, 1);
	dup2(output_fd, 1);
	close(output_fd);
	return (0);
}

//	function that will connect STDIN with the temporary file created with 
//	the heredoc. The right temporary file is determined with the heredoc index.

int	redir_heredoc(t_data *data, int cmdnr, int sole_builtin)
{
	char	*temp_filename;
	int		exit_code;

	temp_filename = create_temp_file_name(data->heredoc_index_array[cmdnr - 1]);
	if (temp_filename == NULL)
		exit_on_error("Error :", 1);
	data->heredoc_index_array[cmdnr -1] += 1;
	exit_code = redir_input(temp_filename, sole_builtin);
	free(temp_filename);
	return (exit_code);
}

/*
**	Function processes the pipe redirections first
**	and then the other redirections based on input file or output file
**	if inpipe_fd == -1 or outpipe_fds == -1 then the pipes are closed
*/

int	process_redir(t_red *red_list, t_data *data, int cmdnbr, int sole_builtin)
{
	int	exit_code;

	exit_code = 0;
	while (red_list != NULL && exit_code == 0)
	{
		if (ft_strcmp(red_list->op, "<") == 0)
			exit_code = redir_input(red_list->file, sole_builtin);
		else if (ft_strcmp(red_list->op, ">") == 0)
			exit_code = redir_output(red_list->file, sole_builtin);
		else if (ft_strcmp(red_list->op, ">>") == 0)
			exit_code = redir_output_append(red_list->file, sole_builtin);
		else if (ft_strcmp(red_list->op, "<<") == 0)
			exit_code = redir_heredoc(data, cmdnbr, sole_builtin);
		red_list = red_list->next;
	}
	return (exit_code);
}
