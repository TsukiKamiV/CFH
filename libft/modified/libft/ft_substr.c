/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:43:52 by luxu              #+#    #+#             */
/*   Updated: 2024/05/22 17:25:15 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t		r_len;
	size_t		s_len;
	size_t	i;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (NULL);
	if (s_len - start > len)
		r_len = len;
	else
		r_len = s_len - start;
	ret = (char *)malloc((r_len + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	while (i < r_len)
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[r_len] = '\0';
	return (ret);
}
