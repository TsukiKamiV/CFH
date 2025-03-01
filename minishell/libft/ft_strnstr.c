/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:48:42 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/23 16:08:15 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_substr(const char *str1, const char *str2, size_t n, size_t i)
{
	size_t	j;

	j = 0;
	while (str1[i + j] && str1[i + j] == str2[j] && i + j < n)
	{
		if (!str2[j + 1])
			return (1);
		j++;
	}
	return (0);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	*str1;
	char	*str2;

	if (*s2 == '\0')
		return ((char *)s1);
	if (n == 0)
		return (NULL);
	str1 = (char *)s1;
	str2 = (char *)s2;
	i = 0;
	while (str1[i] && i < n)
	{
		if (is_substr(str1, str2, n, i))
			return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}
