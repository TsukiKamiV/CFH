/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:15:41 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/23 17:20:15 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
/*
#include <stdio.h>
int	main(void)
{
	char 	*str = "12345689";
	unsigned int	start = 3;
	size_t	len = 2;
	printf("%s", ft_substr(str, start, len));
	return (0);
}
*/
