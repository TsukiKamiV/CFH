#include "../../includes/push_swap.h"

static int	count_words(char *s, char c)
{
	int	count;
	bool	inside_word;
	
	count = 0;
	while (*s)
	{
		inside_word = false;
		while (*s == c)
			++s;
		while (*s != c && *s)
		{
			if (!inside_word)
			{
				++count;
				inside_word = true;
			}
			++s;
		}
	}
	return (count);
}

static char	*get_next_word(char *arg, char set)
{
	static int	cursor;
	char	*next_word;
	int	len;
	int	i;
	
	len = 0;
	i = 0;
	while (arg[cursor] == set)
		++cursor;
	while ((arg[cursor + len] != set) && arg[cursor + len])
		++len;
	next_word = malloc((size_t)len * sizeof(char) + 1);
	if (!next_word)
		return (NULL);
	while ((arg[cursor] != set) && arg[cursor])
		next_word[i++] = arg[cursor++];
	next_word[i] = '\0';
	return (next_word);
}

char	**split_arg(char *arg, char set)
{
	int	words_count;
	char	**ret;
	int	i;
	
	i = 0;
	words_count = count_words(arg, set);
	if (!words_count)
		return (NULL);
	ret = malloc(sizeof(char *) * (size_t)(words_count + 2));
	if (!ret)
		return (NULL);
	while (words_count-- >= 0)
	{
		if (i == 0)
		{
			ret[i] = malloc(sizeof(char));
			if (!ret[i])
				return (NULL);
			ret[i++][0] = '\0';
			continue;
		}
		ret[i++] = get_next_word(arg, set);
	}
	ret[i] = NULL;
	return (ret);
}
