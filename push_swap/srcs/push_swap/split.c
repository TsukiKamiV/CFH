/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:11:15 by luxu              #+#    #+#             */
/*   Updated: 2024/10/06 18:15:58 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

static int	count_words(char *s, char c)
{
	int		count;
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

static char	*get_next_word(char *s, char c)
{
	static int	cursor = 0;
	char		*next_word;
	int			len;
	int			i;

	len = 0;
	i = 0;
	while (s[cursor] == c)
		++cursor;
	while ((s[cursor + len] != c) && (s[cursor + len]))
		++len;
	next_word = malloc((size_t)len * sizeof(char) + 1);
	if (!next_word)
		return (NULL);
	while ((s[cursor] != c) && (s[cursor]))
		next_word[i++] = s[cursor++];
	next_word[i] = '\0';
	return (next_word);
}

char	**split(char *s, char c)
{
	int		words_count;
	char	**ret;
	int		i;

	i = 0;
	words_count = count_words(s, c);
	if (!words_count)
		exit (1);
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
			continue ;
		}
		ret[i++] = get_next_word(s, c);
	}
	ret[i] = NULL;
	return (ret);
}
