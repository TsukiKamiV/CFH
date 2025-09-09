#include "../../includes/miniRT.h"

int	scan_frac(const char *t, int i, int *count)
{
	*count = 0;
	if (t[i] != '.')
		return (i);
	i++;
	while (ft_isdigit(t[i]))
	{
		(*count)++;
		i++;
	}
	return (i);
}
