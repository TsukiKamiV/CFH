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

char	**ft_allocation(size_t n)
{
	char	**ret;

	ret = (char **)malloc((n + 1) * sizeof (char *));
	if (!ret)
		return (NULL);
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	words;
	size_t	index;
	size_t	start;
	size_t	end;

	words = ft_count_words(s, c);
	ret = ft_allocation(words);
	index = 0;
	start = 0;
	while (index < words)
	{
		while (s[start] == c && s[start])
			start++;
		end = start;
		while (s[end] != c && s[end])
			end++;
		ret[index] = ft_substr(s, start, end - start);
		if (!ret[index])
			return (NULL);
		start = end;
		index++;
	}
	ret[index] = NULL;
	return (ret);
}
