/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 10:39:11 by hman          #+#    #+#                 */
/*   Updated: 2021/02/20 13:27:50 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*empty_string(void)
{
	char	*str;

	str = malloc(1);
	if (str == NULL)
		return (NULL);
	*str = '\0';
	return (str);
}

static int	check_set(char c, char const *set)
{
	int	found;

	found = 0;
	while (*set != '\0' && !found)
	{
		if (*set == c)
			found = 1;
		set++;
	}
	return (found);
}

static char const	*trim_begin(char const *s1, char const *set)
{
	char const	*begin_p;
	int			stop;

	stop = 0;
	begin_p = s1;
	while (!stop)
	{
		if (!(check_set(*begin_p, set)))
			stop = 1;
		else
			begin_p++;
	}
	return (begin_p);
}

static char const	*trim_end(char const *s1, char const *set)
{
	char const	*end_p;
	int			stop;

	stop = 0;
	end_p = s1;
	while (!stop)
	{
		if (!(check_set(*end_p, set)))
			stop = 1;
		else
			end_p--;
	}
	return (end_p);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		str_length;
	char const	*begin_p;
	char const	*end_p;
	int			trimmed_str_length;
	char		*trimmed_str;

	if (s1 == NULL)
		return (empty_string());
	str_length = ft_strlen(s1);
	end_p = s1 + str_length - 1;
	begin_p = trim_begin(s1, set);
	if (begin_p > end_p)
		return (empty_string());
	end_p = trim_end((s1 + str_length - 1), set);
	trimmed_str_length = end_p - begin_p + 1;
	trimmed_str = malloc(trimmed_str_length + 1);
	if (trimmed_str == NULL)
		return (NULL);
	ft_strlcpy(trimmed_str, begin_p, trimmed_str_length + 1);
	return (trimmed_str);
}
