/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:20:55 by luxu              #+#    #+#             */
/*   Updated: 2024/05/22 17:01:55 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dest_ptr;
	const unsigned char	*src_ptr;

	i = 0;
	dest_ptr = (unsigned char *)dest;
	src_ptr = (const unsigned char *)src;
	while (i < n)
	{
		dest_ptr[i] = src_ptr[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char src1[] = "Hello World";
	char src2[] = "Hello World";
	//char dest1[50];
	//char dest2[50];

	//ft_memcpy(dest1, src, strlen(src) +1);
	//printf("Copied string ft: %s\n", dest1);

	//memcpy(dest2, src, strlen(src)+1);
	//printf("Copied string lib: %s\n", dest2);

	ft_memcpy(src1 + 7, src1 + 1, 4);
	printf("%s\n", src1);
	memcpy(src2 + 7, src2 + 1, 4);
	printf("%s\n", src2);
}*/
