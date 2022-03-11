#include "../includes/minishell.h"

 void	print_envp(t_env *list)
 {
 	t_env	*current = list;

 	while (current != NULL)
 	{
 		printf("%s=%s\n", current->key, current->value);
 		current = current->next;
 	}
 	printf("\n");
 }

int main(int argc, char **envp)
{
	char	*line;
	t_env	*envplist; 

	if (! argc )
		return (1);

	envplist = envp_copy(envp);
	print_envp(envplist);
 	set_env(&envplist,"A","hello");
	set_env(&envplist,"B","bye");
	print_envp(envplist);

	while (1)
	{
		line = readline(PROMPT);
		//line = "<'input.txt'> $A.txt | ls";
		//line = "<'input.txt'> $A.txt | $B >  ls";
		add_history(line);
		parse_line(line, envplist);
//		free(line);
	}
//	rd_clear_history();
	return (0);
}
