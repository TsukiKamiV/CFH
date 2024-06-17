/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:00:37 by luxu              #+#    #+#             */
/*   Updated: 2024/06/06 13:51:42 by luxu             ###   ########.fr       */
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

static void	ft_free_split(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	index;
	size_t	start;
	size_t	end;
	
	ret = (char **)malloc(sizeof(char **) * (ft_count_words(s, c) + 1));
	if (!ret)
		return (NULL);
	index = 0;
	end = 0;
	while (s[end])
	{
		while (s[end] == c && s[end])
			end++;
		start = end;
		while (s[end] != c && s[end])  
			end++;
		if (end > start) 
		{
			ret[index] = ft_substr(s, start, end - start);
			if (!ret[index++])
		 		return (ft_free_split(ret), NULL);
		}
	}
	return (ret[index] = NULL, ret);
}
