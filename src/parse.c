#include "../includes/minishell.h"

void	create_link_list_element(int location, t_list **list)
{
	t_list *new;

	new = create_new_elem(location);
	if (!new)
		exit(1);
	add_at_the_end(list, new);
}

int count_commands(char *str, t_data *data)
{
	int i;
	int single_quotes;
	int double_quotes;
	int nr_blocks;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	nr_blocks = 0;

	create_link_list_element(-1, &data->line_arg);

	while (str[i] != '\0')
	{
		if (str[i] == 39 && single_quotes == 0 && double_quotes == 0) //single quotes
			single_quotes = 1;
		else if (str[i] == 39 && single_quotes == 1 && double_quotes == 0) // single quotes 
			single_quotes = 0;

		if (str[i] == 34 && single_quotes == 0 && double_quotes == 0) // double quotes
			double_quotes = 1;
		else if (str[i] == 34 && single_quotes == 0 && double_quotes == 1) // double quotes
			double_quotes = 0;

		if (str[i] == '|' && single_quotes == 0 && double_quotes == 0)
		{
			printf("i: %d\n",i);
			create_link_list_element(i, &data->line_arg);
			nr_blocks++;
		}
		i++;
	}
	if (str[i] == '\0')
	{
		nr_blocks++;
		create_link_list_element(ft_strlen(str), &data->line_arg);
	}

	if (single_quotes == 0 && double_quotes == 0)
		printf("blocks: %d\n", nr_blocks);
	else if (single_quotes == 1 || double_quotes == 1)
		printf("error\n");
	return (nr_blocks);
}

void split_blocks(char *str, int nr_blocks, t_data *data)
{
	int i;
	int j;
	int k;
	int size;
	t_list *temp;

	i = 0;
	j = 0;
	temp = data->line_arg;
	data->commands = malloc(sizeof(char *) * (nr_blocks + 1));
	if (!data->commands)
		exit(1);
	data->commands[nr_blocks] = NULL;
	while (i < nr_blocks - 1)
	{
//		if (i == 0)
//			size = temp->next->location - temp->location;
//		else
		size = temp->next->location - temp->location - 1;

		data->commands[i] = malloc(sizeof(char) * (size + 1));
		if (!data->commands[i])
			exit(1);
		data->commands[i][size]= '\0';

		k = 0;
		while (j < temp->next->location)
		{
			data->commands[i][k] = str[j];
			j++;
			k++;
		}
		temp = temp->next;
		i++;
		j++;
	}

	//last block
//	if (nr_blocks == 1)
//		size = ft_strlen(str);
//	else if (nr_blocks > 1) 
	size = temp->next->location - temp->location - 1;

	data->commands[i] = (char *)malloc(sizeof(char) * (size + 1));
	if (!data->commands[i])
		exit(1);
	data->commands[i][size] = '\0';
	k = 0;
	while (str[j] != '\0')
	{
		data->commands[i][k] = str[j];
		j++;
		k++;
	}
}

void parse_line(char *str, t_data *data)
{
	int		i;
	int		nr_blocks;
	char	**blocks;
	t_list	*temp;

	i = 0;
	nr_blocks = count_commands(str, data);
	temp = data->line_arg;
	while (i <= nr_blocks)
	{
		printf("location %d: %d\n", i, temp->location);
		i++;
		temp = temp->next;
	}
	split_blocks(str, nr_blocks, data);
	blocks = data->commands;
	while (*blocks != NULL)
	{
		printf("block: %s\n", *blocks);
		blocks++;
	}
}