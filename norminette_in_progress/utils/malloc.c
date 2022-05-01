/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa&hman@student.codam.nl>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 14:53:48 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 15:52:05 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Function returns a new string without the begining and end quotes
*/

char	*malloc_string(int size)
{
	char	*string;

	string = malloc(sizeof(char) * (size + 1));
	if (!string)
		exit_on_error("Error :", 1);
	string[size] = '\0';
	return (string);
}
