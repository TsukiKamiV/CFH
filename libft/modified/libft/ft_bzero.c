/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:31:42 by luxu              #+#    #+#             */
/*   Updated: 2024/05/22 16:55:18 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
/*
#include <string.h>
#include <stdio.h>
int	main()
{
	char str[50];
	
	strcpy(str, "Hello World");
	puts(str);
	ft_bzero(&str, 5);
	puts(str);
	bzero(&str, 5);
	puts(str);
	return (0);
}*/
