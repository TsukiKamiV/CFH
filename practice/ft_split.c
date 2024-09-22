#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char*	ft_strndup(char *str, int len)
{
	char *ret = NULL;
	int	i = 0;
	ret = (char *)malloc((len + 1) * sizeof(char));
	while (i < len)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	count_words(char *str)
{
	int	i = 0;
	int	j;
	int	count = 0;

	while (str[i])
	{
		j = 0;
		while (str[i + j] && str[i + j] != ' ')
		{
			if (str[i + j + 1] == ' ')
				count++;
			else if (str[i + j + 1] == '\0')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

char	**ft_split(char *str)
{
	char **ret = NULL;
	int	i = 0;
	int	j;
	int	index = 0;
	int	word_count = count_words(str);

	while (i <= word_count)
	{
		j = 0;
		while (str[i + j] && str[i + j] != ' ')
			j++;
		ret[index] = ft_strndup(&str[i], j);
		index++;
		i++;
	}
	ret[index] = NULL;
	return (ret);
} 

int	main()
{
	char *str = "Hello everybody, today is Monday!";
	int	i = 0;
	int	count = count_words(str);
	char **tab = ft_split(str);
	while (i <= count)
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
}
