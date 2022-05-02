/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:53:27 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/02 17:38:36 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_syntax(char **tokens, t_data *data)
{
	write(2, "error syntax\n", 14);
	data->last_exit_code = 258;
	free_string_array(tokens);
}

void	exit_on_error(char *message, int exit_code)
{
	perror(message);
	exit(exit_code);
}

void	exit_no_such_file_error(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": No such file or directory\n", 28);
	exit(127);
}

void	exit_command_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	exit(126);
}
