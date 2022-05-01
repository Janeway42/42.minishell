/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_heredoc_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:51:51 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 17:51:52 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//	function to create the temp file name

char	*create_temp_file_name(int i)
{
	char	*number;
	char	*filename;

	number = ft_itoa(i);
	if (number == NULL)
		exit_on_error("Error :", 1);
	filename = ft_strjoin(".tmp_file_heredoc.", number);
	free(number);
	if (filename == NULL)
		exit_on_error("Error :", 1);
	return (filename);
}

//	function to clean up the created temporary files
//	it will clean up the files from 0.tmp, 1.tmp, etc. until if can't find
//	the next sequentially numbered file in the directory.

void	clean_heredoc_temp_files(void)
{
	int		i;
	int		done;
	char	*filename;

	done = FALSE;
	i = 0;
	while (done == FALSE)
	{
		filename = create_temp_file_name(i);
		if (access(filename, F_OK) == -1)
		{
			free(filename);
			done = TRUE;
			break ;
		}
		if (unlink(filename) == -1)
			exit_on_error("Error :", 1);
		free(filename);
		i++;
	}
}

//	function that counts the total amount of heredoc redirections in 
//	all the commands combined

int	count_heredocs(t_list *cmd_block)
{
	int		count;
	t_red	*redir;

	count = 0;
	while (cmd_block != NULL)
	{
		redir = cmd_block->redirect;
		while (redir != NULL)
		{
			if (ft_strcmp("<<", redir->op) == 0)
				count++;
			redir = redir->next;
		}
		cmd_block = cmd_block->next;
	}
	return (count);
}

//	function that will fill the string array delim with the delimiters
//	defined for the heredocs
//	RETURN	the next position in the string array delim with the number i

int	fill_delim(char **delim, int i, t_red *redir)
{
	while (redir != NULL)
	{
		if (ft_strcmp("<<", redir->op) == 0)
		{
			delim[i] = ft_strdup(redir->file);
			if (delim[i] == NULL)
				exit_on_error("Error :", 1);
			i++;
		}
		redir = redir->next;
	}
	return (i);
}

//	function that gets all the delimiters of the heredocs
//	RETURN	string array with all the delimiters for each heredoc
//			and is array ends with NULL

char	**get_heredoc_delim(t_list *cmd_block)
{
	int		count;
	int		i;
	char	**delim;
	t_red	*redir;

	count = count_heredocs(cmd_block);
	delim = malloc(sizeof (char *) * (count + 1));
	if (delim == NULL)
		exit_on_error("Error :", 1);
	i = 0;
	while (cmd_block != NULL)
	{
		redir = cmd_block->redirect;
		i = fill_delim(delim, i, redir);
		cmd_block = cmd_block->next;
	}
	delim[count] = NULL;
	return (delim);
}
