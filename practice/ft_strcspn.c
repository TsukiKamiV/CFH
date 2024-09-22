#include <stdio.h>
#include <string.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i = 0;
	size_t	j;
	size_t	len = 0;
	while (reject[i] != '\0')
	{
		j = 0;
		while (s[j] != '\0')
		{
			if (s[j] == reject[i] && len >= j)
				len = j;
			j++;
		}
		i++;
	}
	return (len);
}

int main()
{
	char *str = "Hello world";
	char *set = "wo";
	size_t	size = strcspn(str, set);
	size_t	cspn = ft_strcspn(str, set);
	printf("%zd\n", size);
	printf("%zd\n", cspn);
	return (0);
}
