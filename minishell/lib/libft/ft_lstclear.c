/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 14:04:21 by hakaman       #+#    #+#                 */
/*   Updated: 2021/02/20 13:17:48 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_p;

	while (*lst != NULL)
	{
		next_p = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = next_p;
	}
}
