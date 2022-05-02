/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 19:37:05 by hman          #+#    #+#                 */
/*   Updated: 2022/05/01 19:37:09 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//-----------------------------------------------------------------------------
//	function will attempt to change the OLDPWD environment variable to the
//	PWD value
//	RETURN	1 if the PWD value is not found
//			0 if the value has succesfully changed

static int	set_oldpwd(char ***envp_list)
{
	char	*directory;
	char	*temp;

	temp = get_var_value(*envp_list, "PWD");
	if (temp == NULL)
	{
		write(2, "PWD variable couldn't not be found.", 35);
		return (1);
	}
	directory = ft_strjoin("OLDPWD=", temp);
	free(temp);
	if (directory == NULL)
		exit_on_error("Error :", 1);
	set_variable(envp_list, directory);
	free(directory);
	return (0);
}

//	function will attemp to change the PWD environment variable to the current
//	working directory
//	RETURN	1 if it fails
//			0 if it succeeds

static int	set_pwd(char ***envp_list)
{
	char	*directory;
	char	*temp;

	temp = getcwd(NULL, 0);
	if (temp == NULL)
	{
		perror("Couldn't get the current directory :");
		return (1);
	}
	directory = ft_strjoin("PWD=", temp);
	free(temp);
	if (directory == NULL)
		exit_on_error("Error :", 1);
	set_variable(envp_list, directory);
	free(directory);
	return (0);
}

// changes the directory

static int	ft_cd_changing(char *directory, char **args, char ***envp_list)
{
	if (chdir(directory) == -1)
	{
		write(2, "cd : ", 5);
		perror(directory);
		if (*args == NULL)
			free(directory);
		return (1);
	}
	else
	{	
		if (*args == NULL)
			free(directory);
		if (set_oldpwd(envp_list) == 1 || set_pwd(envp_list) == 1)
			return (1);
	}
	return (0);
}

/*
**	will change the current working directory.
**	RETURN	0 if it succeeded
**			1 if is failed
*/

int	ft_cd(char **args, char ***envp_list)
{
	char	*directory;
	int		return_value;

	directory = *args;
	if (directory == NULL)
	{
		directory = get_var_value(*envp_list, "HOME");
		if (directory == NULL)
		{
			write(2, "cd: HOME not set\n", 17);
			return (1);
		}
	}
	return_value = ft_cd_changing(directory, args, envp_list);
	if (return_value == 1)
		return (1);
	return (0);
}
