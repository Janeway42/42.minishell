#include "../includes/minishell.h"

void test(t_list *cmd_blocks, t_data *data)
{

	if (is_it_builtin(cmd_blocks->cmd) == 1)
		execute_builtin(&(data->envplist), cmd_blocks->cmd, data->last_exit_code); 

}

// void	process_commands(t_list *cmd_blocks, t_data *data)
// {
// 	int	pid;
// 	int	wstatus;
// 	int	cmd_nr;
// 	t_list *temp;

// 	temp = ft_last_block(cmd_blocks); // I have the index in each command block
// 	cmd_nr = 1;
// 	while (cmd_nr <= temp->index_cmd)
// 	{



// 	}
// }