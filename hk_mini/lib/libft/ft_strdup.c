/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 20:59:46 by hakaman       #+#    #+#                 */
/*   Updated: 2020/11/04 21:15:41 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate;
	size_t	str_length;

	str_length = ft_strlen(s);
	duplicate = (char *)malloc(str_length + 1);
	if (duplicate == NULL)
		return (NULL);
	ft_strlcpy(duplicate, s, str_length + 1);
	return (duplicate);
}
