/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:58:08 by luxu              #+#    #+#             */
/*   Updated: 2024/05/22 17:03:10 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	value;
	size_t			i;

	ptr = (unsigned char *) str;
	value = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		ptr[i] = value;
		i++;
	}
	return (str);
}
/*
#include <string.h>
#include <stdio.h>

int main(void)
{
    char str[50];
    char c;
    c = '$';

    strcpy(str, "Hello World!");
    puts(str);
    printf("\n");

    ft_memset(str, c, 5);
    puts(str);
    printf("\n");
    memset(str, c, 5);
    puts(str);
}*/
