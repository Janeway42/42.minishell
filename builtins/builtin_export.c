#include "minishell.h"

//-----------------------------------------------------------------------------
/*
**	will check if the environment name is valid
** 	according to
**	https://pubs.opengroup.org/onlinepubs/000095399/basedefs/xbd_chap08.html
**  valid is [A-Z][0-9], the underscore '_' and not start with a digit for a 
**	environmental variable.Bash seems to accept [a-z] also.
**	RETURN	0 if the name is invalid
**			1 if the name is valid
*/

int	is_valid_env_name(char *name)
{
	if (ft_isdigit(*name) || *name == '\0')
		return (0);
	while (*name != '\0')
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (FALSE);
		name++;
	}
	return (TRUE);
}

//	function will swap the strings at element i and i + 1 in the array

static void	check_and_swap(char **sorted_list, int i, int *swapped)
{
	char	**split1;
	char	**split2;
	char	*temp;

	split1 = ft_split_variable(sorted_list[i]);
	split2 = ft_split_variable(sorted_list[i + 1]);
	if (ft_strcmp(split1[0], split2[0]) > 0)
	{
		temp = sorted_list[i];
		sorted_list[i] = sorted_list[i + 1];
		sorted_list[i + 1] = temp;
		*swapped = 1;
	}
	free_string_array(split1);
	free_string_array(split2);
}

//	function that will sort the envp_list and return a copy of the list
//	that is sorted

static char	**sort_envp_list(char **envp_list)
{
	char	**sorted_list;
	int		i;
	int		swapped;

	sorted_list = copy_envp(envp_list);
	swapped = 1;
	while (swapped != 0)
	{
		i = 0;
		swapped = 0;
		while (sorted_list[i + 1] != NULL)
		{
			check_and_swap(sorted_list, i, &swapped);
			i++;
		}
	}
	return (sorted_list);
}

//	function will print out the environmental variables including the variable
//	that don't have a value assigned to it.

void	print_export_list(char **envp_list)
{
	char	**sorted_list;
	char	**split;
	int		i;

	sorted_list = sort_envp_list(envp_list);
	i = 0;
	while (sorted_list[i] != NULL)
	{
		split = ft_split_variable(sorted_list[i]);
		if (split[1] == NULL)
			printf("declare -x %s\n", split[0]);
		else if (ft_strcmp("?", split[0]) != 0)
			printf("declare -x %s=\"%s\"\n", split[0], split[1]);
		free_string_array(split);
		i++;
	}
	free_string_array(sorted_list);
}

/*
**	will export the variables to the envp list after checking if it
*/

int	ft_export(char **args, char ***envp_list)
{
	char	**split;
	int		exit_code;

	exit_code = 0;
	if (args[0] == NULL)
		print_export_list(*envp_list);
	else
	{
		while (*args != NULL)
		{
			split = ft_split_variable(*args);
			if (is_valid_env_name(split[0]) == FALSE)
			{
				write(2, "export : `", 10);
				write(2, split[0], ft_strlen(split[0]));
				write(2, "` : not a valid identifier\n", 27);
				exit_code = 1;
			}
			else
				set_variable(envp_list, *args);
			free_string_array(split);
			args++;
		}
	}
	return (exit_code);
}
