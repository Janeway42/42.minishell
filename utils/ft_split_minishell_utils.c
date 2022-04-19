#include "../includes/minishell.h"

/*
**-------------------------------------------------------------------------
** get the number of strings to be created
** Single quotation ASCII = 39, Double quotation ASCII = 34
*/

// int	check_operator(char *str, int loc)
// {
// 	if (str[loc] == '|' || str[loc] == '<' || str[loc] == '>'
// 		|| str[loc] == 32)
// 		return (1);
// 	if (str[loc - 1] != 39 && str[loc] == 39 && str[loc + 1] != 39)
// 		return (1);
// 	if (str[loc - 1] != 34 && str[loc] == 34 && str[loc + 1] != 34)
// 		return (1);
// 	return (0);
// }

// int	check_operator(char c)
// {
// 	if (c == '|' || c == '<' || c == '>'
// 		|| c == 39 || c == 34 || c == 32)
// 		return (1);
// 	return (0);
// }

// int check_quotes(char *str, int loc)
// {
// 	if (str[loc] == 39 && str[loc + 1] == 39)
// 		return (1);
// 	if (str[loc] == 34 && str[loc + 1] == 34)
// 		return (1);
// 	return (0);
// }

// static int	run_though_quotes(char *str, int loc)
// {
// 	if (str[loc] == 39)
// 	{
// 		loc++;
// 		while (str[loc] != '\0' && str[loc] != 39)
// 			loc++;
// 		if (str[loc] == 39)
// 			loc++;
// 	}
// 	if (str[loc] == 34)
// 	{
// 		loc++;
// 		while (str[loc] != '\0' && str[loc] != 34)
// 			loc++;
// 		if (str[loc] == 34)
// 			loc++;
// 	}
// 	return (loc);
// }

// static int	run_through_elem(char *str, int loc)
// {
// 	if (str[loc] == 39 || str[loc] == 34)
// 			loc = run_though_quotes(str, loc);
// 	else if (str[loc] == '<' || str[loc] == '>')
// 	{
// 		if ((str[loc] == '<' && str[loc + 1] == '<')
// 			|| (str[loc] == '>' && str[loc + 1] == '>'))
// 			loc += 2;
// 		else if ((str[loc] == '<' && str[loc + 1] != '<')
// 			|| (str[loc] == '>' && str[loc + 1] != '>'))
// 			loc++;
// 	}
// 	else if (str[loc] == '|' )
// 		loc++;
// 	return (loc);
// }

// int	count_strings(char *str, char c)
// {
// 	int	i;
// 	int	j;
// 	int	nr_strings;

// 	i = 0;
// 	j = 0;
// 	nr_strings = 0;
// 	while (str[i] != '\0')
// 	{
// 		while (str[i] != '\0' && str[i] == c)
// 			i++;
// 		if (str[i] == '\0')
// 			return (nr_strings);

// 		if (check_operator(str[i]) == 1)
// 		{
// 			if (check_quotes(str, i) == 1)
// 				i = i + 2;
// 			else
// 			{
// 				i = run_through_elem(str, i);
// 				nr_strings++;
// 			}
// 		}
// 		else
// 		{
// 			while (str[i] != '\0')
// 			{
// 				if (check_operator(str[i]) == 1)
// 				{
// 					if (check_quotes(str, i) == 1)
// 						i = i + 2;
// 					else
// 						nr_strings++;
// 				}
// 				i++;
// 			}
// 			nr_strings++;
// 		}
// 	}
// 	return (nr_strings);
// }


// int	count_strings(char *str, char c)
// {
// 	int	i;
// 	int	nr_strings;

// 	i = 0;
// 	nr_strings = 0;
// 	while (str[i] != '\0')
// 	{
// 		while (str[i] != '\0' && str[i] == c)
// 			i++;
// 		if (str[i] == '\0')
// 			return (nr_strings);
// 		if (check_operator(str[i]) == 1)
// 		{
// 			i = run_through_elem(str, i);
// 			nr_strings++;
// 		}
// 		else
// 		{
// 			while (str[i] != '\0' && check_operator(str[i]) == 0)
// 					i++;
// 			nr_strings++;
// 		}
// 	}
// 	return (nr_strings);
// }

//---------------------------------------------------

// int	check_operator(char c)
// {
// 	if (c == '|' || c == '<' || c == '>'
// 		|| c == 39 || c == 34 || c == 32)
// 		return (1);
// 	return (0);
// }

// int check_quotes(char *str, int loc)
// {
// 	if (str[loc] == 39 && str[loc + 1] == 39)
// 		return (1);
// 	if (str[loc] == 34 && str[loc + 1] == 34)
// 		return (1);
// 	return (0);
// }

static int	run_though_quotes(char *str, int loc)
{
	if (str[loc] == 39)
	{
		loc++;
		while (str[loc] != '\0' && str[loc] != 39)
			loc++;
		if (str[loc] == 39)
			loc++;
		return (loc);
	}
	if (str[loc] == 34)
	{
		loc++;
		while (str[loc] != '\0' && str[loc] != 34)
			loc++;
		if (str[loc] == 34)
			loc++;
		return (loc);
	}
	return (loc);
}

int count_strings(char *str, char c)
{
	int	i;
	int	j;
	int	nr_strings;

	i = 0;
	nr_strings = 0;
	while (str[i] != '\0')  
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		if (str[i] == '\0')
			return (nr_strings);
		if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
				i += 2;
			else if ((str[i] == '<' && str[i + 1] != '<') || (str[i] == '>' && str[i + 1] != '>'))
				i++;
			else if (str[i] == '|')
				i++;
			nr_strings++;
		}
		else if (str[i] == 39 || str[i] == 34)
		{
			j = 0;
			if (str[i] == 39)
			{
				while (str[i + j] != '\0' && str[i + j] == 39)
					j++;
				if (j % 2 != 0)
				{
					i = i + (j - 1);
					i = run_though_quotes(str, i);
				}
				else
					i = i + j;
			}
			else if (str[i] == 34)
			{
				while (str[i + j] != '\0' && str[i + j] == 34)
					j++;
				if (j % 2 != 0)
				{
					i = i + (j - 1);
					i = run_though_quotes(str, i);
				}
				else
					i = i + j;
			}
			nr_strings++;
		}
		else
		{
			while (str[i] != '\0' && str[i] != 32 && str[i] != '<' && str[i] != '>' && str[i] != '|')
			{
				if (str[i] == 39 || str[i] == 34)
				{
					j = 0;
					if (str[i] == 39)
					{
						while (str[i + j] != '\0' && str[i + j] == 39)
							j++;
						if (j % 2 != 0)
						{
							i = i + (j - 1);
							i = run_though_quotes(str, i);
						}
						else
							i = i + j;
					}
					else if (str[i] == 34)
					{
						while (str[i + j] != '\0' && str[i + j] == 34)  // double 
							j++;
						if (j % 2 != 0)
						{
							i = i + (j - 1);
							i = run_though_quotes(str, i);
						}
						else
							i = i + j;
					}
				}
				else
					i++;
			}
			nr_strings++;
		}
	}
	return (nr_strings);
}
