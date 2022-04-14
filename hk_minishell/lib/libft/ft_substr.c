/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 13:19:17 by hakaman       #+#    #+#                 */
/*   Updated: 2021/02/20 13:28:23 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	cr_substr(char const *s, char *substr, unsigned int start,
			size_t len)
{
	size_t	i_substr;

	i_substr = 0;
	while (i_substr < len)
	{
		substr[i_substr] = s[start];
		start++;
		i_substr++;
	}
	substr[i_substr] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	str_length;
	char	*substr;

	if (s == NULL)
		return (NULL);
	str_length = ft_strlen(s);
	if (start > str_length)
	{
		substr = malloc(1);
		if (substr == NULL)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if (len > (str_length - start))
		len = str_length - start;
	substr = malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	cr_substr(s, substr, start, len);
	return (substr);
}
