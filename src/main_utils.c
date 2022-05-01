/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:39:45 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 17:43:58 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//	will set the exit code to the '?' environment variable.

void	set_shell_level(t_data *data)
{
	char	*number;
	int		level;
	char	*shelllevel;

	number = get_var_value(data->envplist, "SHLVL");
	level = ft_atoi(number);
	free(number);
	level++;
	number = ft_itoa(level);
	if (number == NULL)
		exit_on_error("Error :", 1);
	shelllevel = ft_strjoin("SHLVL=", number);
	if (shelllevel == NULL)
		exit_on_error("Error :", 1);
	free(number);
	set_variable(&(data->envplist), shelllevel);
	free(shelllevel);
}

/*
** data->term_without_echo.c_lflag &= ~(0001000);
*/

void	set_up_shell_terminal(t_data *data)
{
	if (isatty(0) == 0)
		exit_on_error("Error: ", 1);
	if (tcgetattr(0, &data->term_with_echo) == -1)
		exit_on_error("Exit: ", 1);
	data->term_without_echo = data->term_with_echo;
	data->term_without_echo.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(0, TCSANOW, &data->term_without_echo) == -1)
		exit_on_error("Error: ", 1);
}

/*
** SIGINT The process was “interrupted” (CTRL + C)
** SIGQUIT issued if the user sends a quit signal (CTRL + D)
** SIG_IGN macro defining a signal strategy for signal() = signal is ignored
*/

void	initialize_minishell(int argc, char **argv, char **envp
			, t_data *data)
{
	(void)argc;
	(void)argv;
	data->envplist = copy_envp(envp);
	set_variable(&data->envplist, "OLDPWD");
	set_variable(&data->envplist, "?=0");
	data->inpipe_fd = -1;
	data->outpipe_fds[1] = -1;
	data->last_exit_code = 0;
	set_up_shell_terminal(data);
	set_shell_level(data);
}

//-------------------------------------------------

void	set_exit_code(t_data *data)
{
	char	*number;
	char	*question_var;

	number = ft_itoa(data->last_exit_code);
	if (number == NULL)
		exit_on_error("Error :", 1);
	question_var = ft_strjoin("?=", number);
	if (question_var == NULL)
		exit_on_error("Error :", 1);
	free(number);
	set_variable(&data->envplist, question_var);
	free(question_var);
}
