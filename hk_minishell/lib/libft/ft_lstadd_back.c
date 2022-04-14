/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 19:35:42 by hakaman       #+#    #+#                 */
/*   Updated: 2021/02/20 13:17:10 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp_p;

	if (new != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			temp_p = *lst;
			while (temp_p->next != NULL)
			{
				temp_p = temp_p->next;
			}
			temp_p->next = new;
		}
	}
}
