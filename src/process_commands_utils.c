/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_commands_utils.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:51:17 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 17:51:18 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//	function that will setup the input and output pipe for the command

void	setup_pipe(t_list *cmd_block, t_data *data, int amount_commands)
{
	if (cmd_block->index_cmd != 1)
	{
		data->inpipe_fd = data->outpipe_fds[0];
		data->outpipe_fds[0] = -1;
	}
	if (cmd_block->index_cmd < amount_commands)
	{
		if (pipe(data->outpipe_fds) == -1)
			exit_on_error("Error :", 1);
	}
}

//	function that will process the solo builtin command

void	process_solo_builtin(t_list *cmd_block, t_data *data,
	int *wait_on_child_process)
{
	data->old_stdin = dup(0);
	data->old_stdout = dup(1);
	if (cmd_block->redirect != NULL)
	{
		data->last_exit_code = process_redir(cmd_block->redirect, data, 1,
				TRUE);
	}
	data->last_exit_code = execute_builtin(&data->envplist,
			cmd_block->cmd, data->last_exit_code, FALSE);
	dup2(data->old_stdin, 0);
	dup2(data->old_stdout, 1);
	close(data->old_stdin);
	close(data->old_stdout);
	*wait_on_child_process = FALSE;
}

//	function to count the amount of commands in the command list

int	count_commands(t_list *cmd_block)
{
	int	count;

	count = 0;
	while (cmd_block != NULL)
	{
		count++;
		cmd_block = cmd_block->next;
	}
	return (count);
}

//	function that process the pipe redirections

void	process_pipe_redir(t_data *data)
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
}
