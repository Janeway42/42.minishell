/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: janeway <janeway@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/05 16:01:54 by janeway       #+#    #+#                 */
/*   Updated: 2021/10/15 19:22:56 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_counter_arrays(char const *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

static int	ft_array_length(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static void	*free_array(char **pointer_array, int position)
{
	int	i;

	i = 0;
	while (i < position)
	{
		free(pointer_array[i]);
		i++;
	}
	free(pointer_array);
	return (NULL);
}

static char	**fill(char const *s, int count_arrays, char c, char **pointer_arr)
{
	int	i;
	int	i2;
	int	length;

	i = 0;
	while (i < count_arrays)
	{
		while (*s == c)
			s++;
		length = ft_array_length(s, c);
		pointer_arr[i] = (char *)malloc(sizeof(char) * (length + 1));
		if (!pointer_arr[i])
			return (free_array(pointer_arr, i));
		i2 = 0;
		while (i2 < length)
		{
			pointer_arr[i][i2] = *s;
			s++;
			i2++;
		}
		pointer_arr[i][i2] = '\0';
		i++;
	}
	pointer_arr[i] = NULL;
	return (pointer_arr);
}

char	**ft_split(char const *s, char c)
{
	char	**pointers_arr;
	int		count_arrays;

	if (!s)
		return (NULL);
	count_arrays = ft_counter_arrays(s, c);
	pointers_arr = (char **)malloc(sizeof(char *) * (count_arrays + 1));
	if (!pointers_arr)
		return (NULL);
	pointers_arr = fill(s, count_arrays, c, pointers_arr);
	return (pointers_arr);
}
