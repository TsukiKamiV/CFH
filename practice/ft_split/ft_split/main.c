#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
char*   ft_strndup(char *str, int len)
{
	char *ret = NULL;
	int i = 0;
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int count_words(char *str)
{
	int i = 0;
	int j = 0;
	int count = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] != ' ')
		{
			while (str[i + j] != ' ' && str[i + j])
				j++;
			count++;
			i += j;
			j = 0;
		}
	}
	return (count);
}

char    **ft_split(char *str)
{
	char **ret = NULL;
	int i = 0;
	int j;
	int index = 0;
	int word_count = count_words(str);
	ret = (char **)malloc(word_count * sizeof(char *));
	if (!ret)
		return (NULL);
	while (index < word_count && str[i])
	{
		j = 0;
		while (str[i] == ' ')
			i++;
		while (str[i + j] && str[i + j] != ' ')
			j++;
		ret[index] = ft_strndup(&str[i], j);
		index++;
		i += j;
	}
	ret[index] = NULL;
	return (ret);
}

void	free_memory(char **tab)
{
	int	i = 0;
	int	j;
	if (!tab)
		return;
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free (tab);
}

int main(void)
{
	char *str = "Hello    how are    you";
	int i = 0;
	int count = count_words(str);
	char **tab = ft_split(str);
	while (i <= count)
	{
		printf("%s\n", tab[i]);
		i++;
	}
	free_memory(tab);
	return (0);
}
