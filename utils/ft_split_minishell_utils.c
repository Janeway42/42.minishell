#include "../includes/minishell.h"

static int	run_though_quotes(char *str, int loc, char c)  // duplicate with quote lenght 
{
	if (str[loc] == c)
	{
		loc++;
		while (str[loc] != '\0' && str[loc] != c)
			loc++;
		if (str[loc] == c)
			loc++;
		return (loc);
	}
	return (loc);
}

int count_strings(char *str, char c)
{
	int	i;
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
		else
		{
			while (str[i] != '\0' && str[i] != 32 && str[i] != '<' && str[i] != '>' && str[i] != '|')
			{
				if (str[i] == 39 || str[i] == 34)
				{
					if (str[i] == 39)
						i = run_though_quotes(str, i, 39);
					else if (str[i] == 34)
						i = run_though_quotes(str, i, 34);
				}
				else
					i++;
			}
			nr_strings++;
		}
	}
	return (nr_strings);
}
