/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:13:52 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/23 17:14:59 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srcsize;

	i = 0;
	srcsize = ft_strlen(src);
	if (dstsize == 0)
		return (srcsize);
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
		dst[i] = '\0';
	return (srcsize);
}
/*
int main(void)
{
    char dst[10] = "abc";
    char src[10] = "def";
    size_t dstsize = 10;

    printf("ft_strlcpy: %lld\n", ft_strlcpy(dst, src, dstsize));
    printf("dst: %s\n", dst);
    printf("src: %s\n", src);
    return 0;
}*/
