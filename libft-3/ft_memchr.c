/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:32:27 by luxu              #+#    #+#             */
/*   Updated: 2024/06/03 12:15:05 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	if (s)
	{
		i = 0;
		while (i < n)
		{
			if (*(unsigned char *)(s + i) == (unsigned char)c)
				return ((void *)(s + i));
			i++;
		}
	}
	return (NULL);
}
