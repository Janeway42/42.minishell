#include "minishell.h"

//	function will try to locate the command in the directories set in PATH
//	environmental variable. The char *temp is a function parameter because 
//	of the 25 lines rule of the norminette

static char	*locate_in_path(char *cmd, char **path_dirs, char *temp)
{
	char	*full_path_cmd;
	int		i;
	int		file_exist;

	i = 0;
	file_exist = -1;
	full_path_cmd = NULL;
	while (path_dirs[i] != NULL && file_exist != 0)
	{
		temp = ft_strjoin(path_dirs[i], "/");
		if (temp == NULL)
			exit_on_error("Error :", 1);
		full_path_cmd = ft_strjoin(temp, cmd);
		free(temp);
		if (full_path_cmd == NULL)
			exit_on_error("Error :", 1);
		file_exist = access(full_path_cmd, F_OK);
		if (file_exist == -1)
		{
			free(full_path_cmd);
			full_path_cmd = NULL;
		}
		i++;
	}
	return (full_path_cmd);
}

//	function checks if a command starts with '/', './' or '../'
//	RETURN	1 if starts like mentioned
//			0 if it doesn't start like mentioned.

static int	is_cmd_abs_or_relative(char *cmd)
{
	if (!ft_strncmp("/", cmd, 1) || !ft_strncmp("./", cmd, 2)
		|| !ft_strncmp("../", cmd, 3))
		return (1);
	return (0);
}

//	function will first chechk if the command given is absolute or relatvie
//	if it is it will look if it exist. If command is not absolute or relative
//	it will search in the PATH directories attempt to find the program
//	RETURN	malloced string of the path to the program if found
//			NULL if the command don't exist or is not found in PATH directories

char	*validate_and_locate_cmd(char *cmd, char **envp)
{
	char	*cmd_path;
	char	*temp;
	char	**path_dirs;

	cmd_path = NULL;
	if (is_cmd_abs_or_relative(cmd))
	{
		if (access(cmd, F_OK) == 0)
		{
			cmd_path = ft_strdup(cmd);
			if (cmd_path == NULL)
				exit_on_error("Error :", 1);
		}
	}
	else
	{
		temp = get_var_value(envp, "PATH");
		path_dirs = ft_split(temp, ':');
		free(temp);
		if (path_dirs == NULL)
			exit_on_error("Error :", 1);
		cmd_path = locate_in_path(cmd, path_dirs, NULL);
		free_string_array(path_dirs);
	}	
	return (cmd_path);
}

//gcc validation_cmd.c ft_strcmp.c errors.c envp_utils.c envp_copy.c -L../lib/libft -lft
/*
int	main(int argc, char **argv, char **envp)
{
	if (argv[1] == NULL)
		return (0);
	char *s = validate_and_locate_cmd(argv[1], envp);
	if (s == NULL)
		printf("command not found\n");
	else
		printf("%s is the full path.\n",s);	
	return (0);
}

*/