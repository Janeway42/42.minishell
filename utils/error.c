/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:53:27 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 17:53:28 by cpopa         ########   odam.nl         */
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
