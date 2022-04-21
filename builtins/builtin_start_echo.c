#include "minishell.h"

//-----------------------------------------------------------------------------
//	this function checks if te command is a builtin function or not.
//	RETURN	0 if the command is not one of the builtin functions supported
//			1 if the command is one of the builtin functions supported.

int	is_it_builtin(char *cmd)
{
	const char	*s[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit",
		NULL};
	int			i;

	if (cmd == NULL)
		return (FALSE);
	i = 0;
	while (s[i] != NULL)
	{
		if (ft_strcmp(cmd, s[i]) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

//	it will go through the builtin functions and run the appropriate function
//	RETURN	the exit code of the relevant function
//			-1 if no function has been run.

int	execute_builtin(char ***envp_list, char **args, int last_exit_code)
{
	int		exit_code;
	char	*cmd;

	exit_code = -1;
	cmd = args[0];
	if (ft_strcmp(cmd, "echo") == 0)
		exit_code = ft_echo(&args[1]);
	else if (ft_strcmp(cmd, "cd") == 0)
		exit_code = ft_cd(&args[1], envp_list);
	else if (ft_strcmp(cmd, "pwd") == 0)
		exit_code = ft_pwd(*envp_list);
	else if (ft_strcmp(cmd, "export") == 0)
		exit_code = ft_export(&args[1], envp_list);
	else if (ft_strcmp(cmd, "unset") == 0)
		exit_code = ft_unset(&args[1], envp_list);
	else if (ft_strcmp(cmd, "env") == 0)
		exit_code = ft_env(*envp_list);
	else if (ft_strcmp(cmd, "exit") == 0)
		exit_code = ft_exit(&args[1], last_exit_code);
	return (exit_code);
}

//-----------------------------------------------------------------------------
/*
**	will print out the arguments and end with an newline
** 	flags	: -n	will not end with a newline
*/

//test if one of the args is ""

int	ft_echo(char **args)
{
	int	i;
	int	end_line;

	end_line = 1;
	i = 0;
	if (args[0] != NULL && !ft_strcmp("-n", args[0]))
	{
		end_line = 0;
		i = 1;
	}
	while (args[i] != NULL)
	{
		if (ft_strcmp("-n", args[i]) != 0)
		{
			if (args[i])
				printf("%s", args[i]);
			if (args[i + 1] != NULL)
				printf(" ");
		}
		i++;
	}
	if (end_line)
		printf("\n");
	return (0);
}
