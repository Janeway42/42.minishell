/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 20:03:46 by hakaman       #+#    #+#                 */
/*   Updated: 2021/02/20 13:20:24 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	const unsigned char	*src_p;
	unsigned char		*dest_p;
	size_t				i;

	src_p = (const unsigned char *)src;
	dest_p = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		*dest_p = *src_p;
		if (*src_p == (unsigned char)c)
		{
			dest_p++;
			return (dest_p);
		}
		dest_p++;
		src_p++;
		i++;
	}
	return (NULL);
}
