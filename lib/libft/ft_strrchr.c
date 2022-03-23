/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 21:12:41 by hakaman       #+#    #+#                 */
/*   Updated: 2020/11/09 13:50:32 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*p;
	unsigned char	e;
	int				done;

	p = s + ft_strlen(s);
	e = (unsigned char)c;
	done = 0;
	while (!done)
	{
		if (*p == e)
			return ((char *)p);
		else if (p == s)
			done = 1;
		p--;
	}
	return (NULL);
}
