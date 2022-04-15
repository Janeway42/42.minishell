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

/*
**-------------------------------------------------------------------------
**	Function processes the redirection 
*/

void	process_redir(t_red *red_list, t_data *data)
{
	//do the pipe redirections first
	//if the inpipe_fd is -1 there is no active inputpipe
	if (data->inpipe_fd != -1)
	{
		dup2(data->inpipe_fd, 0);
		close(data->inpipe_fd);
	}
	//if outpipe_fds[1] == -1 means no active outputpipe 
	if (data->outpipe_fds[1] != -1)
	{
		dup2(data->outpipe_fds[1], 1);
		close(data->outpipe_fds[1]);
	}
	//also close the read part of the pipe in the child process
	if (data->outpipe_fds[0] != -1)
		close(data->outpipe_fds[0]);

	//do the other redictions after

	while (red_list != NULL)
	{
		if (ft_strcmp(red_list->op, "<") == 0)
		{

			write(2,"redirect input\n",15);
			redir_input(red_list->file);
		}
		else if (ft_strcmp(red_list->op, ">") == 0)
		{
			write(2,"redirect output\n",16);
			redir_output(red_list->file);
		}
		else if (ft_strcmp(red_list->op, ">>") == 0)
		{
			write(2,"redirect output append\n",23);
			redir_output_append(red_list->file);
		}
//		heredoc
//		else if (ft_strcmp(red_list->op, "<<") == 0)
		red_list = red_list->next;
	}
}




