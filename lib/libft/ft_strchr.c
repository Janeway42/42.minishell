/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 20:19:16 by hakaman       #+#    #+#                 */
/*   Updated: 2020/11/03 21:11:36 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	const char		*p;
	unsigned char	e;
	int				done;

	p = s;
	e = (unsigned char)c;
	done = 0;
	while (!done)
	{
		if (*p == e)
			return ((char *)p);
		else if (*p == '\0' && e != '\0')
			done = 1;
		p++;
	}
	return (NULL);
}
