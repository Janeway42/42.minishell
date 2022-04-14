#include "minishell.h"

void	exec_command(t_cmd_block *cmd_list, t_data *data)
{
	char	*path;
//do the redirections
	process_redir(cmd_list->redirs, data);
//check if it is a builtin command
	if (is_it_builtin(cmd_list->cmd_args[0]))
	{
		data->last_exit_code = execute_builtin(&data->envp_list,
				&cmd_list->cmd_args[0], data->last_exit_code);
		exit(data->last_exit_code);
	}
//if not check if the command exist if not give error
//else execute the command
	else
	{
		path = validate_and_locate_cmd(cmd_list->cmd_args[0], data->envp_list);
		if (path == NULL)
		{
			write(2, cmd_list->cmd_args[0], ft_strlen(cmd_list->cmd_args[0]));
			write(2, ": command not found\n", 20);
			exit(127);
		}
		else
		{
			if (execve(path, cmd_list->cmd_args, data->envp_list))
				exit_on_error(cmd_list->cmd_args[0], 1);
		}
	}
}

//	function to count the amount of commands in the command list

int	count_commands(t_cmd_block *cmd_list)
{
	int	count;

	count = 0;
	while (cmd_list != NULL)
	{
		count++;
		cmd_list = cmd_list->next;
	}
	return (count);
}

//	function that process the command block

void	process_cmds(t_cmd_block *cmd_list, t_data *data)
{
	int	pid;
	int	wstatus;
	int	amount_commands;
	int	cmdnbr;

	amount_commands = count_commands(cmd_list);
	//create all the heredoc files
	cmdnbr = 1;
	while (cmdnbr <= amount_commands)
	{
		//if there is still another command thus pipe is necessary
		// copy the read part of the previous pipe into inpipe_fd
		if (cmdnbr != 1)
		{
				data->inpipe_fd = data->outpipe_fds[0];
				data->outpipe_fds[0] = -1;
		}
		//if not the first command copy read end fd of the previous outpipe
		// to inpipe_fd
		if (cmdnbr < amount_commands)
		{
			if (pipe(data->outpipe_fds) == -1)
				exit_on_error("Error :", 1);
		}
		//check if there are commands at all
		//if it is the only command and it is builtin
		//don't fork and execute the builtin function
		if (amount_commands == 1
			&& is_it_builtin(cmd_list->cmd_args[0]) == TRUE)
		{	
			//do the redirections
			data->last_exit_code = execute_builtin(&data->envp_list,
					cmd_list->cmd_args, data->last_exit_code);
		}
		else
		{
			pid = fork();
			if (pid < 0)
				exit_on_error("Error :", 1);
			else if (pid == 0)
				exec_command(cmd_list, data); //child process
			else
			{
				//still at parent
				//only close the inputfd when not first commmand 
				//because there is no input pipe for the first command.
				if (cmdnbr != 1)
				{
					close(data->inpipe_fd);
					data->inpipe_fd = -1;
				}
				//only close the output write side of pipe if not last command
				//because there is no outputpipe for the last command
				if (cmdnbr != amount_commands)
				{
					close(data->outpipe_fds[1]);
					data->outpipe_fds[1] = -1;
				}
			}
		}
		cmd_list = cmd_list->next;
		cmdnbr++;
	}
//temporary wait for all children processses
	cmdnbr = 1;
	while (cmdnbr <= amount_commands)
	{
		wait(&wstatus);
		cmdnbr++;
	}
}
