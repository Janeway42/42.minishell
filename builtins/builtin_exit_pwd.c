#include "minishell.h"

//-----------------------------------------------------------------------------
//	check is the string is all digits with allowance for the first character to 
//	be	a '-' or a '+' but has to be followed up with a digit.
//	RETURN	1 if string is all digits
//			0 if string is not all digits

static int	is_all_digits(char *s)
{
	if (*s == '\0')
		return (0);
	if (*s == '-' || *s == '+')
	{
		if (s[1] == '\0')
			return (0);
		s++;
	}
	while (*s != '\0')
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

/// convert the string to a long

static long	convert_to_long(char *s, int *overflowed)
{
	long	sum;
	int		sign;

	sum = 0;
	sign = 1;
	*overflowed = FALSE;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s != '\0')
	{
		sum = (sum * 10) + ((*s - 48) * sign);
		s++;
	}
	if (sum != 0 && ((sign == 1 && sum < 0) || (sign == -1 && sum > 0)))
		*overflowed = TRUE;
	return (sum);
}

//	function that will display the error for numeric argument and exit 

static void	ft_exit_error(char *arg)
{
	write(2, "exit\nexit: ", 11);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 27);
	exit(255);
}

//	function will exit the program. The exit code will be set to the number that
//	has been set by 

int	ft_exit(char **args, int last_exit_code)
{
	long	exit_code;
	int		overflowed;

	if (args[0] == NULL)
	{
		write(2, "exit\n", 5);
		exit(last_exit_code % 256);
	}
	if (!is_all_digits(args[0]))
		ft_exit_error(args[0]);
	else if (args[1] != NULL)
		write(2, "exit\nexit: too many arguments\n", 30);
	else
	{
		exit_code = convert_to_long(args[0], &overflowed);
		if (overflowed == 1)
			ft_exit_error(args[0]);
		write(2, "exit\n", 5);
		exit(exit_code % 256);
	}
	return (1);
}

//-----------------------------------------------------------------------------
/*
**	prints out current working directory. Will attempt to get it first from 
**	environment variable. If it fails it will get it with getcwd().
**	RETURN	0 is succesfull
**			-1 if unsuccesfull
*/

int	ft_pwd(char **envp_list)
{
	char	*cwd;

	cwd = get_var_value(envp_list, "PWD");
	if (cwd == NULL)
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
		{	
			write(2, "error can't get current directory information\n", 46);
			return (1);
		}
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
