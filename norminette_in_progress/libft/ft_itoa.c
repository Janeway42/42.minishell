/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 14:49:34 by hman          #+#    #+#                 */
/*   Updated: 2021/02/20 13:16:48 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	convert_number(char *char_number, int n, int size)
{
	int	i;
	int	first_digit_pos;
	int	mod_nbr_sign;
	int	digit;

	first_digit_pos = 0;
	mod_nbr_sign = 1;
	if (n < 0)
	{
		first_digit_pos = 1;
		char_number[0] = '-';
		mod_nbr_sign = -1;
	}
	i = size - 2;
	while (i >= first_digit_pos)
	{
		digit = mod_nbr_sign * (n % (10 * mod_nbr_sign));
		char_number[i] = digit + '0';
		n = n / 10;
		i--;
	}
	char_number[size - 1] = '\0';
}

static int	count_digits(int n)
{
	int	count;

	if (n < 0)
		n = n * -1;
	if (n == 0)
		return (1);
	else
	{
		count = 1;
		while (n > 9)
		{
			n = n / 10;
			count++;
		}
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		negative_sign;
	int		amount_digits;
	char	*char_number;

	negative_sign = 0;
	if (n < 0)
		negative_sign = 1;
	if (n == -2147483648)
		amount_digits = 10;
	else
		amount_digits = count_digits(n);
	char_number = malloc(negative_sign + amount_digits + 1);
	if (char_number == NULL)
		return (NULL);
	convert_number(char_number, n, negative_sign + amount_digits + 1);
	return (char_number);
}
