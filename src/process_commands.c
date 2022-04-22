#include "../includes/minishell.h"

void	exec_path_cmd(t_list *cmd_block, t_data *data)
{
	char	*path;

	path = validate_and_locate_cmd(cmd_block->cmd[0], data->envplist);
	if (path == NULL)
	{
		write(2, cmd_block->cmd[0], ft_strlen(cmd_block->cmd[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	else
	{
		if (execve(path, cmd_block->cmd, data->envplist))
			exit_on_error(cmd_block->cmd[0], 1);
	}
}

// function to execute the command

void	exec_command(t_list *cmd_block, t_data *data)
{
	process_pipe_redir(data);
	process_redir(cmd_block->redirect, data, cmd_block->index_cmd, FALSE);
	if (cmd_block->cmd == NULL)
		exit(0) ;
	if (is_it_builtin(cmd_block->cmd[0]))
	{
		data->last_exit_code = execute_builtin(&data->envplist,
				&cmd_block->cmd[0], data->last_exit_code);
		exit(data->last_exit_code);
	}
	else
		exec_path_cmd(cmd_block, data);
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

//	function that process the command block

void	process_commands(t_list *cmd_block, t_data *data)
{
	pid_t	pid;
	int		amount_commands;
	int		cmdnbr;
	int		need_to_wait_on_child_proces;

	amount_commands = count_commands(cmd_block);
	cmdnbr = 1;
	need_to_wait_on_child_proces = TRUE;
	while (cmdnbr <= amount_commands)
	{
		if (cmdnbr != 1)
		{
				data->inpipe_fd = data->outpipe_fds[0];
				data->outpipe_fds[0] = -1;
		}
		if (cmdnbr < amount_commands)
		{
			if (pipe(data->outpipe_fds) == -1)
				exit_on_error("Error :", 1);
		}
		if (amount_commands == 1 && cmd_block->cmd != NULL
			&& is_it_builtin(cmd_block->cmd[0]) == TRUE)
		{
			data->old_stdin = dup(0);
			data->old_stdout = dup(1);	
			data->last_exit_code = process_redir(cmd_block->redirect, data, 1, TRUE);
			data->last_exit_code = execute_builtin(&data->envplist,	cmd_block->cmd, data->last_exit_code);
			dup2(data->old_stdin,0);
			dup2(data->old_stdout,1);
			need_to_wait_on_child_proces = FALSE;
		}
		else
		{
			pid = fork();
			if (pid < 0)
				exit_on_error("Error :", 1);
			else if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				exec_command(cmd_block, data);
			}
			else
			{
				if (cmdnbr != 1)
				{
					close(data->inpipe_fd);
					data->inpipe_fd = -1;
				}
				if (cmdnbr != amount_commands)
				{
					close(data->outpipe_fds[1]);
					data->outpipe_fds[1] = -1;
				}
			}
		}
		cmd_block = cmd_block->next;
		cmdnbr++;
	}
	if (need_to_wait_on_child_proces == TRUE)
		wait_for_child_processes(pid, amount_commands, data);
}

void	wait_for_child_processes(pid_t last_pid, int amount_commands,
			t_data *data)
{
	int	wstatus;
	int	command_counter;

	waitpid(last_pid, &wstatus, 0);
	data->last_exit_code = WEXITSTATUS(wstatus);
	command_counter = 2;
	while (command_counter <= amount_commands)
	{
		wait(&wstatus);
		command_counter++;
	}
}
