/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:39:56 by luxu              #+#    #+#             */
/*   Updated: 2024/05/31 19:16:44 by luxu             ###   ########.fr       */
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
