/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 15:03:04 by hakaman       #+#    #+#                 */
/*   Updated: 2020/11/09 13:50:44 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			dst_length;
	size_t			src_length;
	size_t			dst_i;
	size_t			src_i;

	dst_i = 0;
	while (dst[dst_i] != '\0' && dst_i < size)
		dst_i++;
	dst_length = dst_i;
	src_length = ft_strlen(src);
	if (dst_length == size)
		return (dst_length + src_length);
	else
	{
		src_i = 0;
		while (src[src_i] != '\0' && dst_i < (size - 1))
		{
			dst[dst_i] = src[src_i];
			dst_i++;
			src_i++;
		}
		dst[dst_i] = '\0';
	}
	return (dst_length + src_length);
}
