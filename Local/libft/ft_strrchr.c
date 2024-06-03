/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:47:44 by luxu              #+#    #+#             */
/*   Updated: 2024/05/31 19:21:13 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*chr;
	size_t	len;

	chr = (char *)s;
	len = ft_strlen(s);
	while (chr[len] != c)
	{
		if (len == 0)
			return (NULL);
		len--;
	}
	return (&chr[len]);
}
