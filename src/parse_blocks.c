#include "../includes/minishell.h"

void	fill_cmd_block(char *str, t_list **element, t_data *data)
{
	int		i;
	int		cmd_filled;
	char	**temp;
	
	i = 0;
	cmd_filled = 0;

	temp = ft_split(str[i], ' ');

	while (temp[i] != NULL)
	{
		if (ft_input(temp[i]) == 1)  // has <
		{
			(*element)->input = temp[i + 1];
			i++;
		}
		if (ft_output(temp[i]) == 1)  // has >
		{
			(*element)->output = temp[i + 1];
			i++;
		}

		if (cmd_filled == 0)
		{
			(*element)->cmd = temp[i];
			cmd_filled = 1;
		}

		if (cmd_filled == 1)
		{
			if (!(*element)->arguments)
				(*element)->arguments = temp[i];
			else
				ft_strjoin((*element)->arguments, temp[i]);
		}
		i++;
	}
	free_double(temp);
}

void	run_blocks(t_data **data)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = (*data)->line_arg;
	while ((*data)->commands[i] != NULL)
	{
		fill_cmd_block((*data)->commands[i], &temp, data);
		i++;
		temp = temp->next;
	}
}