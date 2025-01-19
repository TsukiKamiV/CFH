/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:53:29 by lpantign          #+#    #+#             */
/*   Updated: 2024/12/23 16:10:48 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*s)
	{
		if (*s == uc)
			return ((char *)s);
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*new_tab;
	int		size;
	int		i;

	i = 0;
	new_tab = NULL;
	size = (int)ft_strlen(src);
	new_tab = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_tab)
		return (NULL);
	while (i <= size)
	{
		new_tab[i] = src[i];
		i++;
	}
	new_tab[size] = '\0';
	return (new_tab);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;
	int		total_len;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = (char *)malloc(sizeof(char) * (total_len + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i++] = s2[j++];
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	unsigned int		i;
	char				*substring;

	i = 0;
	substring = NULL;
	if (!str)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(str))
		return (ft_strdup(""));
	if (ft_strlen(str) - start < len)
		len = ft_strlen(str) - start;
	substring = malloc(sizeof(char) * len + 1);
	if (!substring)
		return (NULL);
	while (i < len && str[start + i])
	{
		substring[i] = str[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
