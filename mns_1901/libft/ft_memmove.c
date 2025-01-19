/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:04:34 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/27 01:37:14 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 ** Moves len bytes from src to dst. 
 ** If dst overlaps with src, handles the overlap 
 ** by copying bytes in reverse order.
 ** @param dst - destination pointer
 ** @param src - source pointer
 ** @param len - number of bytes to move
 ** @return pointer to dst
 **/
static void	*move(unsigned char *dst, unsigned char *src, size_t len)
{
	if (dst >= src)
	{
		src += len;
		dst += len;
		while (len)
		{
			dst--;
			src--;
			*dst = *src;
			len--;
		}
	}
	else
	{
		while (len)
		{
			*dst = *src;
			len--;
			dst++;
			src++;
		}
	}
	return ((void *)dst);
}

/**
 ** Moves len bytes from src to dst, ensuring correct behavior
 ** for overlapping memory areas.
 ** @param dst - destination pointer
 ** @param src - source pointer
 ** @param len - number of bytes to move
 ** @return pointer to dst
 **/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*data_d;
	unsigned char	*data_s;

	if (!src && !dst)
		return (NULL);
	data_d = (unsigned char *)dst;
	data_s = (unsigned char *)src;
	move(data_d, data_s, len);
	return (dst);
}
