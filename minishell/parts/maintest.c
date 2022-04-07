#include "minishell.h"

//for testing
#include <readline/readline.h>
#include <readline/history.h>

t_cmd_block *create_cmd_block()
{
	t_cmd_block *first= malloc(sizeof (t_cmd_block));
	char *cmd_first[]={"ls","-la",NULL};
	first->cmd_args = cmd_first;
	first->inputfd = 0;
	first->outputfd = 1;
	first->redirs = NULL;
	first->cmdnbr = 1;
	return (first);
}

int main(int argc, char **argv, char **envp)
{
	int		last_exit_code;
	char 	**envp_list;
	
	last_exit_code = 0;
	envp_list = copy_envp(envp);	

/*
	t_cmd_block *cmd_list = create_cmd_block();
	while (cmd_list != NULL)
	{
		if (cmd_list->cmdnbr == 1 && is_it_builtin(cmd_list->cmd_args[0]) == 1)
			last_exit_code = execute_builtin(&envp_list, cmd_list->cmd_args, last_exit_code);
		else
		{	
			//piping should be done here
			int pid = fork();
			if (pid == 0)
			{
				//redirections should be done here
				if (is_it_builtin(cmd_list->cmd_args[0]) == 1)
					last_exit_code = execute_builtin(&envp_list, cmd_list->cmd_args, last_exit_code);
				else
				{

					execve(cmd_list->cmd_args[0], cmd_list->cmd_args,envp);
				}
			}	
		}
		
		cmd_list = cmd_list->next;
	}
 */

	char	*input;
	char 	**split;
	int		done;
	done = 0;
	while(!done)
	{
		input = readline("testshell>");
		if (input != NULL)
		{
			split = ft_split(input, ' ');
			if (split[0] != NULL)
			{
				if (is_it_builtin(split[0]) == 1)
					last_exit_code = execute_builtin(&envp_list, split, last_exit_code);
				if (ft_strcmp("done", split[0]) == 0)
				{
					printf("done and will exit\n");
					done = 1;
				}
			}
			free_string_array(split);
		}
		free(input);
	}
	free_string_array(envp_list);
	while(1);
	return (last_exit_code);
}
