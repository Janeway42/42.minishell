#include "../includes/minishell.h"

 void	print_envp(t_env *list)   //erase when no longer neccessary 
 {
 	t_env	*current = list;

 	while (current != NULL)
 	{
 		printf("%s,%s\n", current->key, current->value);
 		current = current->next;
 	}
 	printf("\n");
 }

static void	initialize_data(t_data **data, char **envp)
{
	(*data)->envplist = copy_envp(envp);
	set_variable(&(*data)->envplist,"A = hello");
	set_variable(&(*data)->envplist,"B = bye");
	(*data)->last_exit_code = 0;
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	*data;

	if (!argc )
		return (1);
	(void)argv;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (-1);  // check what type of error it needs to return
	initialize_data(&data, envp);
	
//	print_envp((data->envplist);
//	set_env(&data->envplist,"A","hello");
//	set_env(&data->envplist,"B","bye");
//	print_envp(data->envplist);

	while (1)
	{
		line = readline(PROMPT);
//		line = "12345|12345|12345";
//		line = "< src/main.c grep line | grep l| wc -l";
		//line = "<'input.txt'> $A.txt | ls";
		//line = "<'input.txt'> $A.txt | $B >  ls";
		add_history(line);
		parse_line(line, data);
//		free(line);
	}
//	rl_clear_history();
	return (0);
}
