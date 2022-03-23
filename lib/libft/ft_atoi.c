/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 09:23:01 by hakaman       #+#    #+#                 */
/*   Updated: 2021/02/20 13:12:40 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <limits.h>

static int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	convert_atoi(const char *s, int sign)
{
	int				done;
	unsigned long	result;

	result = 0;
	done = 0;
	while (!done)
	{
		if (*s >= '0' && *s <= '9')
			result = (result * 10) + (*s - 48);
		else
			done = 1;
		if (result > LONG_MAX && sign == 1)
			return (-1);
		else if ((result > ((unsigned long)LONG_MAX) + 1) && sign == -1)
			return (0);
		s++;
	}
	return (result);
}

int	ft_atoi(const char *s)
{
	size_t	i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	while (s[i] != '\0' && is_white_space(*s))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	result = convert_atoi(s, sign);
	return (result * sign);
}
