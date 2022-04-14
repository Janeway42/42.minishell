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
		if (is_valid_env_name(*args) == 0)
		{
			printf("unset : '%s' : not a valid identifier\n", *args);
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
		printf("PWD variable couldn't not be found.");
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

/*
**	will change the current working directory.
**	RETURN	0 if it succeeded
**			1 if is failed
*/

int	ft_cd(char **args, char ***envp_list)
{
	int		return_value;

	if (*args == NULL)
		return (0);
	if (chdir(*args))
	{
		perror(*args);
		return (1);
	}
	else
	{
		if (set_oldpwd(envp_list) || set_pwd(envp_list))
			return (1);
	}
	return (0);
}
