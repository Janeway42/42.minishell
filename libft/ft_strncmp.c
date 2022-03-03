/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/24 15:26:45 by cpopa         #+#    #+#                 */
/*   Updated: 2022/01/24 15:30:24 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (i >= n || (s1[i] == '\0' && s2[i] == '\0'))
			return (0);
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
}
