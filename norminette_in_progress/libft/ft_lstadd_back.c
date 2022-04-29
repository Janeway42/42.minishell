/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: janeway <janeway@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/22 10:23:11 by janeway       #+#    #+#                 */
/*   Updated: 2021/10/15 19:21:39 by janeway       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd_back(t_stack **x, t_stack *element)
{
	t_stack	*temp;

	temp = *x;
	if (*x != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = element;
		element->prev = temp;
	}
	else
		*x = element;
}
