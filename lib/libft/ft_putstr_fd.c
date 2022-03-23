/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 14:51:27 by hakaman       #+#    #+#                 */
/*   Updated: 2021/02/20 13:30:44 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (fd == -1)
		write(1, "Error: Invalid File Descriptor", 30);
	else if (s == NULL)
		write(1, "Error: Input string is a NULL pointer", 37);
	else
	{
		i = ft_strlen(s);
		write(fd, s, i);
	}
}
