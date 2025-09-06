#include "../../includes/miniRT.h"

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
