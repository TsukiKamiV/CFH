/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:32:27 by luxu              #+#    #+#             */
/*   Updated: 2024/05/22 17:00:53 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == c)
			return ((void *)(ptr + i));
		i++;
	}
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>
int	main()
{
	char buffer[] = {'a', 'b', 'c', '\0'};
	char c = 'b';
	void *result_ft = ft_memchr(buffer, c, sizeof(buffer));
    	if (result_ft != NULL) 
	        printf("ft_memchr: Found '%c' at position: %ld\n", c, (char *)result_ft - buffer);
	else 
        	printf("ft_memchr: '%c' not found\n", c); 
}*/
