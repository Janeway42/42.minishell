/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_start_echo.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:33:47 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 17:33:49 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

int	execute_builtin(char ***envp_list, char **args, int last_exit_code,
		int child_process)
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
		exit_code = ft_exit(&args[1], last_exit_code, child_process);
	return (exit_code);
}

//-----------------------------------------------------------------------------

//	check if string is a valid flag in this case -n
//	RETURN : 	0 if it is not a valid flag
//				1 if it is a valid flag

int	valid_flag(char *arg)
{
	int	i;

	if (ft_strncmp(arg, "-", 1) != 0)
		return (FALSE);
	i = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*
**	will print out the arguments and end with an newline
** 	flags	: -n	will not end with a newline
*/

int	ft_echo(char **args)
{
	int	i;
	int	end_line;

	end_line = 1;
	i = 0;
	while (args[i] != NULL && valid_flag(args[i]))
	{
		end_line = 0;
		i++;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL && args[i + 1][0] != '\0')
			printf(" ");
		i++;
	}
	if (end_line == 1)
		printf("\n");
	return (0);
}

//	extra function to accomodate the norm for ft_export

int	ft_export_error(char *args)
{
	write(2, "export : `", 10);
	write(2, args, ft_strlen(args));
	write(2, "`: not a valid identifier\n", 27);
	return (1);
}
