/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 19:03:48 by hakaman       #+#    #+#                 */
/*   Updated: 2021/02/20 13:22:35 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	appending(char **dest, const char *src)
{
	while (*src != '\0')
	{
		**dest = *src;
		(*dest)++;
		src++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_length;
	size_t	s2_lenght;
	char	*joinedstr;
	char	*joinedstr_p;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_length = ft_strlen(s1);
	s2_lenght = ft_strlen(s2);
	joinedstr = malloc(s1_length + s2_lenght + 1);
	if (joinedstr == NULL)
		return (NULL);
	joinedstr_p = joinedstr;
	appending(&joinedstr_p, s1);
	appending(&joinedstr_p, s2);
	*joinedstr_p = '\0';
	return (joinedstr);
}
