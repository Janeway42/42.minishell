/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cpopa <cpopa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/01 17:52:58 by cpopa         #+#    #+#                 */
/*   Updated: 2022/05/01 17:52:59 by cpopa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** rl_replace_line("", 0); replaces the cotents of rl_line_buffer with ""
** rl_on_new_line(); tells the update functions we have moved onto a new 
** (empty) line, usually after outputting a newline.
** rl_redisplay(); change what's displayed on the screen to reflect
** the current contents of rl_line_buffer.
*/

void	sig_handler(int sig_no)
{
	if (sig_no == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

//either put this function in seperate file or a special signals file
// signal handling for the heredoc

void	heredoc_sighandler(int sig_no)
{
	if (sig_no == SIGINT)
	{
		clean_heredoc_temp_files();
		exit(1);
	}
}

void	set_default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
