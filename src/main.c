#include "../includes/minishell.h"

int main()
{
	t_data	*data;
	char	*line;
//	int status;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (1);
	data->line_arg = NULL;

	while (1)
	{
		line = readline(PROMPT);
//		line = "grep l";
		add_history(line);
//		if (line == NULL)
//			rd_clear_history();

		parse_line(line, data);
//		status = execute(arguments);

//		free(line);
	}
//	rd_clear_history();
	return (0);
}
