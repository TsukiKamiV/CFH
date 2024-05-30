/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:33:38 by luxu              #+#    #+#             */
/*   Updated: 2024/05/22 17:22:58 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	l_len;

	l_len = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (j < l_len && i + j < len && big[i + j] == little[j])
			j++;
		if (j == l_len)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int main() 
{
    const char *largestring = "Foo Bar Baz";
    const char *test_cases[] = { "Bar", "Baz", "Foo", "", "NotFound" };
    size_t lengths[] = { 4, strlen(largestring), strlen(largestring), strlen(largestring), strlen(largestring) };
    for (int i = 0; i < 5; i++) {
        char *ptr = ft_strnstr(largestring, test_cases[i], lengths[i]);
        printf("Test %d: %s\n", i + 1, ptr ? ptr : "NULL");
    }
    return 0;
}
*/
