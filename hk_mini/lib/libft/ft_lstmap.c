/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 16:22:40 by hakaman       #+#    #+#                 */
/*   Updated: 2021/02/20 13:19:27 by hakaman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
				void (*del)(void *))
{
	t_list	*new_list;
	t_list	*tmp_elem;

	new_list = NULL;
	while (lst != NULL)
	{
		tmp_elem = malloc(sizeof(t_list));
		if (tmp_elem == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		tmp_elem->content = f(lst->content);
		tmp_elem->next = NULL;
		if (tmp_elem->content == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, tmp_elem);
		lst = lst->next;
	}
	return (new_list);
}
