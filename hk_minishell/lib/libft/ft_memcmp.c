/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 18:21:47 by hakaman       #+#    #+#                 */
/*   Updated: 2021/02/20 13:20:44 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*s1p;
	const unsigned char	*s2p;

	i = 0;
	s1p = s1;
	s2p = s2;
	if (n == 0)
		return (0);
	else
	{
		while (i < n)
		{
			if (!(s1p[i] == s2p[i]))
				return (s1p[i] - s2p[i]);
			i++;
		}
	}
	return (0);
}
