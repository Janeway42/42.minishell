/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: janeway <janeway@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/05 16:22:12 by janeway       #+#    #+#                 */
/*   Updated: 2021/10/15 19:24:14 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_compare(char i)
{
	if (i == ' '
		|| i == '\n'
		|| i == '\t'
		|| i == '\v'
		|| i == '\f'
		|| i == '\r')
		return (1);
	return (0);
}

static int	atoi_overflow(unsigned long value, int sign)
{
	if (value >= LONG_MAX - 1 && sign == 1)
		return (-1);
	if (value >= LONG_MAX - 1 && sign == -1)
		return (0);
	else
		return ((int)(value * sign));
}

int	ft_atoi(const char *nptr)
{
	int				i;
	int				sign;
	unsigned long	value;

	i = 0;
	sign = 1;
	value = 0;
	if (!*nptr)
		return (0);
	while (ft_compare(nptr[i]) == 1)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	if (nptr[i] < '0' || nptr[i] > '9')
		return (0);
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		value = value * 10 + (nptr[i] - '0');
		i++;
	}
	return (atoi_overflow(value, sign));
}
