/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:00:37 by luxu              #+#    #+#             */
/*   Updated: 2024/05/31 20:28:35 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_words(char const *s, char c)
{
	size_t	count;
	int		i;
	int		j;

	count = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			while (s[i + j] != c && s[i + j])
				j++;
			count++;
			i = i + j;
			j = 0;
		}
	}
	return (count);
}

char	**ft_alloc_arr(size_t n)
{
	char	**ret;

	ret = (char **)malloc((n + 1) * sizeof (char *));
	if (!ret)
		return (NULL);
	return (ret);
}

size_t	ft_skip_set(size_t start, char const *s, char c)
{
	while (s[start] == c && s[start])
		start++;
	return (start);
}

size_t	ft_cut_words(size_t end, char const *s, char c)
{
	while (s[end] != c && s[end])
		end++;
	return (end);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	words;
	size_t	index;
	size_t	start;
	size_t	end;

	words = ft_count_words(s, c);
	ret = ft_alloc_arr(words);
	if (!ret || !s)
		return (NULL);
	index = 0;
	start = 0;
	while (index < words)
	{
		start = ft_skip_set(start, s, c);
		end = start;
		end = ft_cut_words(end, s, c);
		ret[index] = ft_substr(s, start, end - start);
		if (!ret[index])
		{
			free (ret);
			return (NULL);
		}
		start = end;
		index++;
	}
	ret[index] = NULL;
	return (ret);
}
