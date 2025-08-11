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
		count++;
	return (count);
}

void	free_multiple_tab(int count, ...)
{
	va_list	ap;
	char 	**ptr;
	int		i;
	
	va_start(ap, count);
	i = 0;
	while (i < count)
	{
		ptr = va_arg(ap, char **);
		if (ptr)
			free_tab(ptr);
		i++;
	}
	va_end(ap);
}

void	free_tab(char **tab)
{
	int	i;
	
	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
