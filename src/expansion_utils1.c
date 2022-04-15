#include "../includes/minishell.h"

/*
** Bash variable can contain only letters, numbers and underscore
** The first character of the name can not be a diggit
** Function looks at whether those conditions are met
*/

static int	validity_name(char c, int location)
{
	int	n;

	n = (int) c;
	if (location == 0 && ft_isdigit(c) == 1)
		return (1);
	if (ft_isdigit(c) == 1 || ft_isalpha(n) == 1 || n == '_')
		return (0);
	return (1);
}

/*
** Function identifies the variable name from the input string
*/

static char	*get_variable_name(char *str, int loc)
{
	int		i;
	int		size;
	char	*name;

	i = 0;
	size = 0;
	while (validity_name(str[loc + size], size) == 0 && str[loc + size] != '\0')
		size++;
	if (size == 0)
		return (NULL);
	name = malloc(sizeof(char) * (size + 1));
	if (!name)
		return (NULL);
	name[size] = '\0';
	while (i < size)
	{
		name[i] = str[loc + i];
		i++;
	}
	return (name);
}

static char	*get_value_from_envp(char *name, char **envp)
{
	int		i;
	int		s_name;
	char	*value;
	char	**temp;

	i = 0;
	s_name = ft_strlen(name);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(name, envp[i], s_name) == 0 && envp[i][s_name] == '=')
		{
			temp = ft_split(envp[i], '=');
			value = ft_strdup(temp[1]);
			free_double(&temp);
			return (value);
		}
		i++;
	}
	return (NULL);
}

/*
**-------------------------------------------------------------------------
** Function replaces the variable $name with the correct variable value
*/

char	*replace_dollar(char *str, char **envplist)
{
	int		i;
	char	*name;
	char	*node_val;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			name = get_variable_name(str, i + 1);
			if (name == NULL)
				node_val = "";
			else
			{
				node_val = get_value_from_envp(name, envplist);
				if (node_val == NULL)
					node_val = "";
			}
			str = insert_variable_value(str, node_val, i, ft_strlen(name));
			i += ft_strlen(node_val) - 1;
		}
		i++;
	}
	return (str);
}

/*
**-------------------------------------------------------------------------
** Function detects the presence of $
*/

int	dollar_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
