/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:38:00 by luxu              #+#    #+#             */
/*   Updated: 2024/06/03 13:03:23 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(src);
	if (size > 0)
	{
		i = 0;
		while (i < size -1 && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (s_len);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
    char src[] = "Hello, world!";
    char dest[20]; // Make sure dest has enough space

    // Testing ft_strlen
    size_t src_len = ft_strlen(src);
    printf("Length of source string: %zu\n", src_len);

    // Testing ft_strlcpy
    size_t copied_len = ft_strlcpy(dest, src, 5);
    printf("Copied string: %s\n", dest);
    printf("Length of copied string: %zu\n", copied_len);
    
    return 0;
}*/
