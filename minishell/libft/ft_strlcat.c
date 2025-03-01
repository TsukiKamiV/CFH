/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:11:37 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/23 17:12:21 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	dst_len = ft_strlen(dst);
	src_len = 0;
	while (src[src_len] && dst_len + 1 < dstsize)
	{
		dst[dst_len] = src[src_len];
		dst_len++;
		src_len++;
	}
	dst[dst_len] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[src_len]));
}
/*
int main(void)
{
    char dst[10] = "abc";
    char src[10] = "def";
    size_t dstsize = 10;

    // Flag lld pour afficher size_t qui est un long long int
    printf("dst: %s\n", dst);
    printf("src: %s\n", src);
    printf("ft_strlcat: %lld\n", ft_strlcat(dst, src, dstsize));
    printf("dst now: %s\n", dst);
    return 0;
}*/
