/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 15:13:42 by hakaman       #+#    #+#                 */
/*   Updated: 2021/02/20 13:21:08 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
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
		write(fd, "\n", 1);
	}
}
