/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:39:56 by luxu              #+#    #+#             */
/*   Updated: 2024/05/22 17:02:25 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;
	unsigned char	temp[100];
	size_t			i;

	if (n == 0 || dest == src)
		return (dest);
	dest_ptr = (unsigned char *) dest;
	src_ptr = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		temp[i] = src_ptr[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		dest_ptr[i] = temp[i];
		i++;
	}
	return (dest_ptr);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char str1[] = "Hello, World!";
	char str2[] = "Hello, World!";

	printf("Original src: %s\n", str1);
	ft_memmove(str1 + 7, str1 + 1, 6);
	memmove(str2 + 7, str2 + 1, 6);
	printf("%s\n", str1);
	printf("%s\n", str2);
	return (0);
}

int main()
{
    char str[] = "Hello, World!";
    char dest1[50];
    char dest2[50];
    printf("%s\n", str);
    ft_memmove(dest1, str, 0);
    printf("%s\n", dest1);
    memmove(dest2, str, 0);
    printf("%s\n", dest2);
    return (0);
}*/
