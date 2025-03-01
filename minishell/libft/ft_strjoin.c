/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:09:50 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/23 17:07:48 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
/*
int main(void)
{
    char *str;
    char *str2;
    str = "Hello ";
    str2 = "la lune";
    printf("%s\n", ft_strjoin(str, str2));
    return (0);
}*/
