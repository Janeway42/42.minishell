/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: janeway <janeway@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/21 17:30:00 by janeway       #+#    #+#                 */
/*   Updated: 2021/10/15 19:23:27 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_stack	*ft_lstlast(t_stack *x)
{
	t_stack	*last;

	if (!x)
		return (NULL);
	last = x;
	while (last->next != NULL)
		last = last->next;
	return (last);
}
