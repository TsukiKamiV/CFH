/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:43:52 by luxu              #+#    #+#             */
/*   Updated: 2024/06/03 12:06:18 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	ret_len;
	char	*ret;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		ret = (char *)malloc(1);
		if (ret)
			ret[0] = '\0';
		return (ret);
	}
	ret_len = s_len - start;
	if (ret_len > len)
		ret_len = len;
	ret = (char *)malloc((ret_len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s + start, ret_len + 1);
	return (ret);
}
