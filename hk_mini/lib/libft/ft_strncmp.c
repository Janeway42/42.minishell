/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 14:44:38 by hakaman       #+#    #+#                 */
/*   Updated: 2021/02/20 13:23:50 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*s1p;
	const unsigned char	*s2p;

	i = 0;
	s1p = (const unsigned char *)s1;
	s2p = (const unsigned char *)s2;
	if (n != 0)
	{
		while (i < n)
		{
			if (!(s1p[i] == s2p[i]) || s1p[i] == '\0')
			{
				if ((s1p[i] - s2p[i]) < 0)
					return (-1);
				else if ((s1p[i] - s2p[i]) > 0)
					return (1);
				else
					return (0);
			}
			i++;
		}
	}
	return (0);
}
