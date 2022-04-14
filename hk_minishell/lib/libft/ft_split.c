/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/08 17:27:18 by hakaman       #+#    #+#                 */
/*   Updated: 2021/02/20 13:22:13 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*next_string(char const **start_p, char c)
{
	char const	*end_p;
	size_t		str_length;
	char		*substring;

	while (**start_p == c)
		(*start_p)++;
	end_p = *start_p;
	while (*end_p != c && *end_p != '\0')
		end_p++;
	str_length = end_p - *start_p;
	substring = malloc(str_length + 1);
	if (substring == NULL)
		return (NULL);
	ft_strlcpy(substring, *start_p, str_length + 1);
	*start_p = end_p;
	return (substring);
}

static int	count_string_parts(char const *s, char c)
{
	size_t	amount;
	int		toggle;

	amount = 0;
	toggle = 0;
	while (*s != '\0')
	{
		if (*s != c && toggle == 0)
		{
			amount++;
			toggle = 1;
		}
		else if (*s == c)
			toggle = 0;
		s++;
	}
	return (amount);
}

static void	clear_string_array(char **split_strings, int i)
{
	while (i >= 0)
	{
		if (split_strings[i] != NULL)
			free(split_strings[i]);
		i--;
	}
	free(split_strings);
}

char	**ft_split(char const *s, char c)
{
	char		**split_strings;
	char const	*next_p;
	size_t		amount_strings;
	size_t		i;

	if (s == NULL)
		return (NULL);
	amount_strings = count_string_parts(s, c);
	split_strings = malloc((amount_strings + 1) * sizeof(char *));
	if (split_strings == NULL)
		return (NULL);
	i = 0;
	next_p = s;
	while (i < amount_strings)
	{
		split_strings[i] = next_string(&next_p, c);
		if (split_strings[i] == NULL)
		{
			clear_string_array(split_strings, i);
			return (NULL);
		}
		i++;
	}
	split_strings[i] = NULL;
	return (split_strings);
}
