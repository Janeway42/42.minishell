/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 15:22:52 by hakaman       #+#    #+#                 */
/*   Updated: 2021/02/20 13:21:41 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	displaynbr(int n, int fd)
{
	char	c;

	if (n > 9)
		displaynbr(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd == -1)
		write(1, "Error: Invalid File Descriptor", 30);
	else
	{
		if (n == -2147483648)
			write(fd, "-2147483648", 11);
		else
		{
			if (n < 0)
			{
				write(fd, "-", 1);
				n = n * -1;
			}
			displaynbr(n, fd);
		}
	}
}
