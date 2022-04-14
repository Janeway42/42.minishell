/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 13:43:32 by hman          #+#    #+#                 */
/*   Updated: 2020/11/13 14:05:38 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dest_p;
	const unsigned char	*src_p;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	dest_p = (unsigned char *)dest;
	src_p = (const unsigned char *)src;
	while (i < n)
	{
		*dest_p = *src_p;
		src_p++;
		dest_p++;
		i++;
	}
	return (dest);
}
