/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:47:07 by lpantign          #+#    #+#             */
/*   Updated: 2024/06/03 12:09:54 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	if (n == 0)
		return (dst);
	if (src == NULL && dst == NULL)
		return (NULL);
	str1 = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	while (i < n)
	{
		str1[i] = str2[i];
			i++;
	}
	return (dst);
}
