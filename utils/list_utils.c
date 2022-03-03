#include "../includes/minishell.h"

t_list *create_new_elem(int number)
{
	t_list	*new_elem;

	new_elem = malloc(sizeof(t_list));
	if (!new_elem)
		return (NULL);
	new_elem->location = number;
	new_elem->block.fd_input = 0;
	new_elem->block.fd_output = 1;
	new_elem->block.cmd = NULL;
	new_elem->block.arguments = NULL;
	new_elem->next = NULL;
	new_elem->prev = NULL;
	return (new_elem);
}

void	add_at_the_end(t_list **line_arg, t_list *element)
{
	t_list	*temp;

	temp = *line_arg;
	if (*line_arg != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = element;
		element->prev = temp;
	}
	else
		*line_arg = element;
}