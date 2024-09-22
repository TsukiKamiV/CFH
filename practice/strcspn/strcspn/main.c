#include <stdio.h>
#include <string.h>

/*size_t  ft_strcspn(const char *s, const char *reject)
{
	size_t  i = 0;
	size_t  j;
	size_t  len = 0;
	while (reject[i] != '\0')
	    {
	        j = 0;
	        while (s[j] != '\0')
			{
				if (s[j] == reject[i] && (len >= j || len == 0))
					len = j;
				j++;
			}
	        i++;
	    }
	return (len);
	}*/

size_t  ft_strcspn(const char *s, const char *reject)
{
	int     i = 0;
	int     j = 0;
	
	while (s[i] != '\0')
	{
		j = 0;
		while (reject[j] != '\0')
		{
			if(s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

 int main()
 {
	char *str = "Good morning Mr. Bean";
	char *set = "hifi";
	size_t  size = strcspn(str, set);
	size_t  cspn = ft_strcspn(str, set);
	printf("%zd\n", size);
	printf("%zd\n", cspn);
	return (0);
}
