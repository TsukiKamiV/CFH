/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:13:59 by luxu              #+#    #+#             */
/*   Updated: 2024/05/22 17:05:33 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	res;

	i = 0;
	j = 0;
	res = 0;
	while (dest[i])
		i++;
	while (src[res])
		res++;
	if (size < i)
		res += size;
	else
		res += i;
	while (src[j] && i + 1 < size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (res);
}
/*
#include <string.h>
#include <stdio.h>
int main()
{
	char src[50] = "Hello";
	char dest[50] = "How are you";

	size_t size = 20;

    printf("Before strlcat:\n");
    printf("dest: '%s'\n", dest);
    printf("src: '%s'\n", src);

    size_t result = ft_strlcat(dest, src, size);

    printf("\nAfter strlcat:\n");
    printf("dest: '%s'\n", dest);
    printf("src: '%s'\n", src);
    printf("Returned length: %zu\n", result);

    return 0;
}*/
