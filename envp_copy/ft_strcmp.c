#include <stddef.h>
#include "../includes/minishell.h"

/*
**	compare string s1 with s2 
**	RETURN	-1 if s1 is smaller than s2
**			0 if s1 is equal to s2
**			1 if s1 is greater than s2
*/

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;
	const unsigned char	*s1p;
	const unsigned char	*s2p;

	i = 0;
	s1p = (const unsigned char *)s1;
	s2p = (const unsigned char *)s2;
	while (s1p[i] == s2p[i] && s1p[i] != '\0')
	{
		i++;
	}
	if ((s1p[i] - s2p[i]) < 0)
		return (-1);
	else if ((s1p[i] - s2p[i]) > 0)
		return (1);
	return (0);
}
