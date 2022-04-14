/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 15:41:22 by hakaman       #+#    #+#                 */
/*   Updated: 2020/11/13 14:05:33 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dest_p;
	const unsigned char	*src_p;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_p = (unsigned char *)dest;
	src_p = (const unsigned char *)src;
	if (dest_p < src_p)
		ft_memcpy(dest_p, src_p, n);
	else
	{
		i = n;
		while (i > 0)
		{
			dest_p[i - 1] = src_p[i - 1];
			i--;
		}
	}
	return (dest);
}
