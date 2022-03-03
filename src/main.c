#include "../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int count_commands(char *str, t_data *data)
{
	int i;
	int single_quotes;
	int double_quotes;
	int nr_blocks;
	t_list *new;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	nr_blocks = 0;

	new = create_new_elem(0);
	if (!new)
		exit(1);
	add_at_the_end(&data->line_arg, new);
	
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
			new = create_new_elem(i);
			if (!new)
				exit(1);
			add_at_the_end(&data->line_arg, new);
			printf("location %d: %d\n", i, data->line_arg->location);
			nr_blocks++;
		}
		i++;
	}
	if (str[i] == '\0')
		nr_blocks++;
	
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

	i = 0;
	j = 0;
	data->commands = malloc(sizeof(char *) * (nr_blocks + 1));
	if (!data->commands)
		exit(1);
	data->commands[nr_blocks] = NULL;
	while (i < nr_blocks)
	{
		size = data->line_arg->location - data->line_arg->next->location;
		data->commands[i] = malloc(sizeof(char) * (size + 1));
		if (!data->commands[i])
			exit(1);
		data->commands[i]= NULL;
		k = 0;
		while (j < data->line_arg->location)
		{
			data->commands[i][k] = str[j];
			j++;
			k++;
		}
		data->line_arg++;
		i++;
	}

	//last block
	size = ft_strlen(str) - data->line_arg->location;
	data->commands[i] = (char *)malloc(sizeof(char) * (size + 1));
	if (!data->commands[i])
		exit(1);
	data->commands[i] = NULL;
	k = 0;
	while (str[j] != '\0')
	{
		data->commands[i][j] = str[j];
		j++;
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
	while (i < nr_blocks)
	{
		printf("location %d: %d\n", i, temp->location);
		i++;
		temp++;
	}

	split_blocks(str, nr_blocks, data);
	blocks = data->commands;
	while (*blocks)
	{
		ft_putstr_fd(*blocks, 1);
		blocks++;
	}
	// count comands
	// break individual comands into blocks
}

int main()
{
	t_data	*data;
	char	*line;
//	int status;

	data = malloc(sizeof(data) * 1);
	if (!data)
		return (1);
	data->line_arg = NULL;

	while (1)
	{
		line = readline(PROMPT);
		add_history(line);
//		if (line == NULL)
//			rd_clear_history();

		parse_line(line, data);
//		print_arguments(arguments);
//		status = execute(arguments);

		free(line);
	}
//	rd_clear_history();
	return (0);
}