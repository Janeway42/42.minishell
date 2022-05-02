/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_commands.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:50:51 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/02 16:31:25 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_path_cmd(t_list *cmd_block, t_data *data)
{
	char	*path;
	int		exist;

	path = validate_and_locate_cmd(cmd_block->cmd[0], data->envplist, &exist);
	if (path == NULL)
	{
		if (exist == TRUE)
			exit_command_not_found(cmd_block->cmd[0]);
		else if (exist == FALSE)
			exit_no_such_file_error(cmd_block->cmd[0]);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(path, cmd_block->cmd, data->envplist))
		{
			if (access(path, X_OK))
				exit_on_error(cmd_block->cmd[0], 126);
			exit_on_error(cmd_block->cmd[0], 1);
		}
	}
}

// function to execute the command

void	exec_command(t_list *cmd_block, t_data *data)
{
	process_pipe_redir(data);
	process_redir(cmd_block->redirect, data, cmd_block->index_cmd, FALSE);
	if (cmd_block->cmd == NULL)
		exit(0);
	if (is_it_builtin(cmd_block->cmd[0]))
	{
		data->last_exit_code = execute_builtin(&data->envplist,
				&cmd_block->cmd[0], data->last_exit_code, TRUE);
		exit(data->last_exit_code);
	}
	else
		exec_path_cmd(cmd_block, data);
}

//	function that will process the command by creating a child process

void	fork_command(t_list *cmd_block, t_data *data, pid_t *pid,
	int amount_commands)
{
	*pid = fork();
	if (*pid < 0)
		exit_on_error("Error :", 1);
	else if (*pid == 0)
		exec_command(cmd_block, data);
	else
	{
		if (cmd_block->index_cmd != 1)
		{
			close(data->inpipe_fd);
			data->inpipe_fd = -1;
		}
		if (cmd_block->index_cmd != amount_commands)
		{
			close(data->outpipe_fds[1]);
			data->outpipe_fds[1] = -1;
		}
	}
}

//	function that process the command block

void	process_commands(t_list *cmd_block, t_data *data)
{
	pid_t	pid;
	int		amount_commands;
	int		wait_on_child_process;

	amount_commands = count_commands(cmd_block);
	wait_on_child_process = TRUE;
	while (cmd_block != NULL && cmd_block->index_cmd <= amount_commands)
	{
		setup_pipe(cmd_block, data, amount_commands);
		if (amount_commands == 1 && cmd_block->cmd != NULL
			&& is_it_builtin(cmd_block->cmd[0]) == TRUE)
			process_solo_builtin(cmd_block, data, &wait_on_child_process);
		else
			fork_command(cmd_block, data, &pid, amount_commands);
		cmd_block = cmd_block->next;
	}
	if (wait_on_child_process == TRUE)
		wait_for_child_processes(pid, amount_commands, data);
}

void	wait_for_child_processes(pid_t last_pid, int amount_commands,
			t_data *data)
{
	int	wstatus;
	int	command_counter;
	int	termsig;

	waitpid(last_pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		data->last_exit_code = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		termsig = WTERMSIG(wstatus);
		if (termsig == 2)
			data->last_exit_code = 130;
		else if (termsig == 3)
		{
			data->last_exit_code = 131;
			write(2, "Quit: 3", 7);
		}
		write(2, "\n", 1);
	}
	command_counter = 2;
	while (command_counter <= amount_commands)
	{
		wait(&wstatus);
		command_counter++;
	}
}
