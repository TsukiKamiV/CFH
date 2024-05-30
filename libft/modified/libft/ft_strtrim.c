#include "libft.h"

int	is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	unsigned char	*start;
	unsigned char	*end;
	size_t	s1_len;
	size_t	ret_len;

	if (!s1 || !set)
		return (NULL);
	ret = NULL;
	s1_len = ft_strlen(s1);
	start = (unsigned char *)s1;
	end = (unsigned char *)s1 + s1_len - 1;
	while (*start && is_in_set(*start, set))
		start++;
	while (end >= start && is_in_set(*end, set))
		end--;
	ret_len = end - start + 1;
	ft_memcpy(ret, start, ret_len);
	if (ret == NULL)
		return (NULL);
	return (ret);
}

#include <stdio.h>
int main()
{
	char const * s = "Hello world Hello";
	char const * set = "Hello";
	char *res = ft_strtrim(s, set);
	printf("%s\n", res);
	return (0);
}
