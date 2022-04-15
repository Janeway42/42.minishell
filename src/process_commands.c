#include "../includes/minishell.h"

void execute_command(t_list *cmd_blocks, t_data *data)
{
	char *path;

	process_redir(cmd_blocks->redirect, data);
	if (is_it_builtin(cmd_blocks->cmd[0]))
	{
		data->last_exit_code = execute_builtin(&data->envplist, &cmd_blocks->cmd[0], data->last_exit_code);
		exit(data->last_exit_code);
	}
	else
	{
		path = validate_and_locate_cmd(cmd_blocks->cmd[0], data->envplist);
		if (path == NULL)
		{
			write(2, cmd_blocks->cmd[0], ft_strlen(cmd_blocks->cmd[0]));
			write(2, ": command not found\n", 20);
			exit(127);
		}
		else
		{
			if (execve(path, cmd_blocks->cmd, data->envplist) == -1)
				exit_on_error(cmd_blocks->cmd[0], 1);
		}
	}
}

void	process_commands(t_list *cmd_blocks, t_data *data)
{
	pid_t	pid;
	int		wstatus;
	int		cmd_nr;
	int		amount_cmd;

	amount_cmd = ft_last_block(cmd_blocks)->index_cmd;
	cmd_nr = 1;
	while (cmd_nr <= amount_cmd)
	{
		if (cmd_nr != 1)
		{
			data->inpipe_fd = data->outpipe_fds[0];
			data->outpipe_fds[0] = -1;
		}
		if (cmd_nr < amount_cmd && pipe(data->outpipe_fds) == -1)
			exit_on_error("Error: ", 1);
		/*----------------------------------------------------*/
		if (amount_cmd == 1 && is_it_builtin(cmd_blocks->cmd[0]) == TRUE)
		{
			// redirection 
			data->last_exit_code = execute_builtin(&data->envplist, cmd_blocks->cmd, data->last_exit_code);
		}
		else
		{
			pid = fork();
			if (pid == -1)
				exit_on_error("Error: ", 1);
			else if (pid == 0)
				execute_command(cmd_blocks, data);
			else
			{
				if (cmd_nr != 1)
				{
					close(data->inpipe_fd);
					data->inpipe_fd = -1;
				}
				if (cmd_nr != amount_cmd)
				{
					close(data->outpipe_fds[1]);
					data->outpipe_fds[1] = -1;
				}
			}
		}
		/*----------------------------------------------------*/

		cmd_blocks = cmd_blocks->next;
		cmd_nr++;
	}
	cmd_nr = 1;
	while (cmd_nr <= amount_cmd)
	{
		wait(&wstatus);
		cmd_nr++;
	}
}