/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 13:24:01 by hakaman       #+#    #+#                 */
/*   Updated: 2021/02/20 13:24:50 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	s2_length;
	int		found;

	if (*s2 == '\0')
		return ((char *)s1);
	else
	{
		s2_length = ft_strlen(s2);
		i = 0;
		found = 0;
		while (i < n)
		{
			if (s1[i] == s2[0] && s2_length <= (n - i))
			{
				found = (!(ft_strncmp(&s1[i], s2, s2_length)));
				if (found)
				{
					return ((char *)&s1[i]);
				}
			}
			i++;
		}
	}
	return ((void *) 0);
}
