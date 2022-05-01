/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_env_unset.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:33:20 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 18:56:45 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//-----------------------------------------------------------------------------
/*
**	will delete the variable from the envp_list
*/

int	ft_unset(char **args, char ***envp_list)
{
	int	exit_code;

	exit_code = 0;
	while (*args != NULL)
	{
		if (is_valid_env_name(*args) == FALSE)
		{
			write(2, "unset : `", 9);
			write(2, *args, ft_strlen(*args));
			write(2, "` : not a valid identifier\n", 27);
			exit_code = 1;
		}
		else
			delete_variable(envp_list, *args);
		args++;
	}
	return (exit_code);
}

//-----------------------------------------------------------------------------
/*
**	will print out all the variables that has a value attached to it
**	and as long the key is not '?'
*/

int	ft_env(char **envp_list)
{
	char	**split;
	int		i;

	i = 0;
	while (envp_list[i] != NULL)
	{
		split = ft_split_variable(envp_list[i]);
		if (split[1] != NULL && ft_strcmp("?", split[0]) != 0)
			printf("%s=%s\n", split[0], split[1]);
		free_string_array(split);
		i++;
	}
	return (0);
}
