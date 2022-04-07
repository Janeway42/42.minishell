/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/08 15:16:00 by hakaman       #+#    #+#                 */
/*   Updated: 2020/11/12 12:19:25 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	str_length;
	char	*result_str;

	if (s == NULL || f == NULL)
		return (NULL);
	str_length = ft_strlen(s);
	result_str = malloc(str_length + 1);
	if (result_str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		result_str[i] = f(i, s[i]);
		i++;
	}
	result_str[i] = '\0';
	return (result_str);
}
