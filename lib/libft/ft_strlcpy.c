/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 09:43:10 by hakaman       #+#    #+#                 */
/*   Updated: 2020/11/14 09:44:01 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_length;
	size_t	i;

	if (dst == NULL || src == NULL)
		return (0);
	src_length = ft_strlen(src);
	if (size == 0)
		return (src_length);
	else
	{
		i = 0;
		while (src[i] != '\0' && (i < (size - 1)))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_length);
}
