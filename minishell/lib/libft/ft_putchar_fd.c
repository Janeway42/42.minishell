/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 14:03:31 by hakaman       #+#    #+#                 */
/*   Updated: 2021/02/20 13:30:06 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	unsigned char	u;

	u = (unsigned char)c;
	if (fd == -1)
		write(1, "Error: Invalid File Descriptor", 30);
	else
		write(fd, &u, 1);
}
