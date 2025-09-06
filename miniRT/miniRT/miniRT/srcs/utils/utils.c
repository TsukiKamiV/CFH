#include "../../includes/miniRT.h"

int	ft_isspace(char c)
{
	return (c == ' '  ||
			c == '\t' ||
			c == '\n' ||
			c == '\v' ||
			c == '\f' ||
			c == '\r');
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_count_size(char **tokens)
{
	int	count;
	
	if (!tokens)
		return (0);
	count = 0;
	while (tokens[count])
	//{
	//	printf("%s\n", tokens[count]);
	//	count++;
	//}
		count++;
	return (count);
}


