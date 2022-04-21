#include "../includes/minishell.h"

/*
**	Function redirects STDIN to inputfile
*/

void	redir_input(char *filename)
{
	int	input_fd;

	input_fd = open(filename, O_RDONLY);
	if (input_fd == -1)
		exit_on_error(filename, 1);
	dup2(input_fd, 0);
	close(input_fd);
}

/*
** Function redirects STDOUT to outfile (non-append)
*/

void	redir_output(char *filename)
{
	int	output_fd;

	output_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (output_fd == -1)
		exit_on_error(filename, 1);
	dup2(output_fd, 1);
	close(output_fd);
}

/*
**	Funcion that redirect STDOUT to outfile (append)
*/

void	redir_output_append(char *filename)
{
	int	output_fd;

	output_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0755);
	if (output_fd == -1)
		exit_on_error(filename, 1);
	dup2(output_fd, 1);
	close(output_fd);
}

//	function that will connect STDIN with the temporary file created with 
//	the heredoc. The right temporary file is determined with the heredoc index.

void	redir_heredoc(t_data *data, int cmdnr)
{
	char	*temp_filename;

	temp_filename = create_temp_file_name(data->heredoc_index_array[cmdnr - 1]);
	if (temp_filename == NULL)
		exit_on_error("Error :", 1);
	data->heredoc_index_array[cmdnr -1] += 1;
	redir_input(temp_filename);
	free(temp_filename);
}

/*
**	Function processes the pipe redirections first
**	and then the other redirections based on input file or output file
**	if inpipe_fd == -1 or outpipe_fds == -1 then the pipes are closed
*/

void	process_redir(t_red *red_list, t_data *data, int cmdnbr)
{
	if (data->inpipe_fd != -1)
	{
		dup2(data->inpipe_fd, 0);
		close(data->inpipe_fd);
	}
	if (data->outpipe_fds[1] != -1)
	{
		dup2(data->outpipe_fds[1], 1);
		close(data->outpipe_fds[1]);
	}
	if (data->outpipe_fds[0] != -1)
		close(data->outpipe_fds[0]);
	while (red_list != NULL)
	{
		if (ft_strcmp(red_list->op, "<") == 0)
			redir_input(red_list->file);
		else if (ft_strcmp(red_list->op, ">") == 0)
			redir_output(red_list->file);
		else if (ft_strcmp(red_list->op, ">>") == 0)
			redir_output_append(red_list->file);
		else if (ft_strcmp(red_list->op, "<<") == 0)
			redir_heredoc(data, cmdnbr);
		red_list = red_list->next;
	}
}

/*
**-------------------------------------------------------------------------
**	Function processes the pipe redirections first
**	and then the other redirections based on input file or output file
**	if inpipe_fd == -1 or outpipe_fds == -1 then the pipes are closed


void	process_redir(t_red *red_list, t_data *data)
{
	if (data->inpipe_fd != -1)
	{
		dup2(data->inpipe_fd, 0);
		close(data->inpipe_fd);
	}
	if (data->outpipe_fds[1] != -1)
	{
		dup2(data->outpipe_fds[1], 1);
		close(data->outpipe_fds[1]);
	}
	if (data->outpipe_fds[0] != -1)
		close(data->outpipe_fds[0]);
	while (red_list != NULL)
	{
		if (ft_strcmp(red_list->op, "<") == 0)
		{
			write(2, "redirect input\n", 15);
			redir_input(red_list->file);
		}
		else if (ft_strcmp(red_list->op, ">") == 0)
		{
			write(2, "redirect output\n", 16);
			redir_output(red_list->file);
		}
		else if (ft_strcmp(red_list->op, ">>") == 0)
		{
			write(2, "redirect output append\n", 23);
			redir_output_append(red_list->file);
		}
//		heredoc
//		else if (ft_strcmp(red_list->op, "<<") == 0)
		red_list = red_list->next;
	}
}
*/